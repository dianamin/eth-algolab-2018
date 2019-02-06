#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
#include <cmath>

using namespace std;

int n, m, k;

vector <int> h;
vector < vector <int> > graph;


void read() {
	cin >> n >> m >> k;
	h = vector <int>(n);
	graph = vector < vector <int> >(n);

	for (int i = 0; i < n; i++)
		cin >> h[i];

	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
	}
}

vector <int> liniarization;
vector <int> temp;

vector < vector <int> > rminq;
vector < vector <int> > rmaxq;

void liniarize(int v) {
	liniarization.push_back(h[v]);

	for (int i = 0; i < graph[v].size(); i++) {
		int u = graph[v][i];

		liniarize(u);
		liniarization.push_back(h[v]);
	}
}

void liniarize() {
	liniarization.clear();
	liniarize(0);
}

void compute_rmq() {
	int lines = 1;
	int elems = liniarization.size();
	while (lines < elems) lines = lines << 1;

	rminq = vector < vector <int> > (lines, vector <int>(elems));
	rmaxq = vector < vector <int> > (lines, vector <int>(elems));

	for (int i = 0; i < elems; i++) {
		//cout << liniarization[i] << ' ';
		rminq[0][i] = rmaxq[0][i] = liniarization[i];
	}
	//cout << '\n';

	for (int l = 1; (1 << l) <= elems; l++) {
		int len = (1 << (l - 1));

		for (int i = 0; i + len < elems; i++) {
			rminq[l][i] = min(rminq[l - 1][i], rminq[l - 1][i + len]);
			rmaxq[l][i] = max(rmaxq[l - 1][i], rmaxq[l - 1][i + len]);
			//cout << rmaxq[l][i] << ' ';
		}
		//cout << "len: " << len * 2;
		//cout << endl;
	}
}

pair <int, int> get_extremes(int a, int b) {
	int len = b - a + 1;
	int lg = log2(len);

	int rmin = min(rminq[lg][a], rminq[lg][b - (1 << lg) + 1]);
	int rmax = max(rmaxq[lg][a], rmaxq[lg][b - (1 << lg) + 1]);

	return make_pair(rmin, rmax);
}

bool is_feasible(int from_index, int to_index) {
	pair <int, int> p = get_extremes(from_index, to_index);
	int diff = p.second - p.first;
	return diff <= k;
}

int index_in_lin;
vector <int> path;
vector <int> real_path;
vector <bool> sol;

void try_to_solve(int v, int lev) {
	path[lev] = index_in_lin++;
	real_path[lev] = v;
	if (lev >= m - 1) {
		if (is_feasible(path[lev - m + 1], path[lev])) {
			//pair <int, int> p = get_extremes(path[lev - m + 1], index_in_lin);
			//int diff = p.second - p.first;
			//cout << real_path[lev - m + 1] << ' ' << diff << endl;
			sol[real_path[lev - m + 1]] = true;
		} 
	}

	for (int i = 0; i < graph[v].size(); i++) {
		int u = graph[v][i];

		try_to_solve(u, lev + 1);

		path[lev] = index_in_lin++;
	}
}


void solve() {
	liniarize();
	compute_rmq();

	index_in_lin = 0;
	real_path = vector <int>(n);
	path = vector <int>(n);
	sol = vector <bool>(n, false);
	try_to_solve(0, 0);

	bool found = false;
	for (int i = 0; i < n; i++)
		if (sol[i]) {
			found = true;
			cout << i << ' ';
		}
	if (!found) cout << "Abort mission";
	cout << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while(t--) {
		read();
		solve();
	}
}