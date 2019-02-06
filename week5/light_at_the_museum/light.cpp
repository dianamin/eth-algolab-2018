#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
int half, half2;
vector <int> goal;
vector < vector <int> > lights;

int sums[1 << 17];
int sums2[1 << 17];
multimap <int, int> other_sums;

void read() {
    cin >> n >> m;
    lights = vector < vector <int> >(n, vector <int> (2 * m, 0));
    goal = vector <int> (m);
    for (int i = 0; i < m; i++) 
    	cin >> goal[i];
    for (int i = 0; i < n; i++)
    	for (int j = 0; j < m; j++)
    		cin >> lights[i][2 * j] >> lights[i][2 * j + 1];
}

void compute_sums(int room) {
	for (int mask = 0; mask < (1 << half); mask++) {
		int sum = 0;
		for (int i = 0; i < half; i++)
			if (mask & (1 << i)) sum += lights[i][2 * room + 1];
			else sum += lights[i][2 * room];
		sums[mask] = sum;
	}


	for (int mask = 0; mask < (1 << half2); mask++) {
		int sum = 0;
		for (int i = 0; i < half2; i++)
			if (mask & (1 << i)) sum += lights[half + i][2 * room + 1];
			else sum += lights[half + i][2 * room];
		if (room == 0) other_sums.insert(make_pair(sum, mask));
		sums2[mask] = sum;
	}
}

int count_switched(int mask, int l) {
	int cnt = 0;
	for (int i = 0; i < l; i++)
		if (mask & (1 << i)) cnt++;
	//cout << mask << ' ' << cnt << endl;
	return cnt;
}

void solve() {
	half = (n + 1) / 2;
	half2 = n - half;

	other_sums.clear();
	
	compute_sums(0);


	vector < pair <int, int> > candidates;
	vector < pair <int, int> > new_candidates;
	for (int mask = 0; mask < (1 << half); mask++) {
		int crt_goal = goal[0] - sums[mask];

		if (crt_goal < 0) continue;

		pair<multimap<int, int>::iterator, multimap<int, int>::iterator> configs;
		configs = other_sums.equal_range(crt_goal);
		for (multimap <int, int> :: iterator it = configs.first;
			 it != configs.second; it++) {
			if (it->first != crt_goal) continue;
			candidates.push_back(make_pair(mask, it->second));
		}
	}

	for (int room = 1; room < m; room++) {
		compute_sums(room);

		for (vector < pair<int, int> > :: iterator it = candidates.begin();
			 it != candidates.end(); it++) {
			if (sums[it->first] + sums2[it->second] == goal[room])
				new_candidates.push_back(*it);
		}

		candidates.clear();
		candidates = new_candidates;
		new_candidates.clear();
	}
	
	if (candidates.size() == 0) {
		cout << "impossible" << '\n';
		return;
	}

	int sol = n;
	for (vector < pair <int, int> > :: iterator it = candidates.begin();
		 it != candidates.end(); it++) {
		sol = min(sol, count_switched(it->first, half) + 
					   count_switched(it->second, half2));
	}
	cout << sol << '\n';
}


int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
	while(t--) {
		read();
		solve();
	}
	return 0;
}