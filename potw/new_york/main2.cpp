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

multiset <int> set_min;
multiset <int> set_max;

vector <int> path;
vector <bool> sol;

void DFS(int v, int lev) {
	set_min.insert(h[v]);
	set_max.insert(-h[v]);

	path[lev] = v;

	int removed;
	if (lev >= m) {
		removed = h[path[lev - m]];
		set_min.erase(set_min.find(removed));
		set_max.erase(set_max.find(-removed));
	}

	if (lev >= m - 1) {
		int h_min = *(set_min.begin());
		int h_max = -*(set_max.begin());

		if (h_max - h_min <= k) {
			sol[path[lev - m + 1]] = true;
		}
	}

	for (int i = 0; i < graph[v].size(); i++) {
		int u = graph[v][i];
		DFS(u, lev + 1);
	}

	set_min.erase(set_min.find(h[v]));
	set_max.erase(set_max.find(-h[v]));

	if (lev >= m) {
		set_min.insert(removed);
		set_max.insert(-removed);
	}
}


void solve() {
	set_min.clear();
	set_max.clear();

	path = vector <int>(n);
	sol = vector <bool>(n);

	DFS(0, 0);


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