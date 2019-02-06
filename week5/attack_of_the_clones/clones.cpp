#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int n, m;
vector < pair <int, int> > jedi;

vector < pair <int, int> > overlapping;
vector < pair <int, int> > non_overlapping;

void read() {
    cin >> n >> m;
    jedi = vector < pair <int, int> >(n);

    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        jedi[i] = make_pair(a, b);
    }
}

int get_min_overlaps_point() {
	map <int, int> counter;
	counter[0] = 0;
	for (int i = 0; i < n; i++) {
		if (!counter.count(jedi[i].first)) counter[jedi[i].first] = 0;
		if (!counter.count(jedi[i].second)) counter[jedi[i].second] = 0;
		counter[jedi[i].first]++;
		counter[jedi[i].second]--;
		if (jedi[i].first > jedi[i].second) counter[0]++;
	}

	int min_overlaps = n;
	int crt_overlaps = 0;
	int min_point = 0;
	for (map <int, int> :: iterator it = counter.begin();
		 it != counter.end(); it++) {
		crt_overlaps += it->second;
		// cout << it->first << ' ' << crt_overlaps << '\n';
		if (crt_overlaps < min_overlaps) {
			min_overlaps = crt_overlaps;
			min_point = it->first;
		}
	}
	return min_point;
}

void fix_jedis(int min_point) {
	overlapping.clear();
	non_overlapping.clear();
	//cout << min_point << endl;
	for (int i = 0; i < n; i++) {
		int a = jedi[i].first;
		int b = jedi[i].second;
		if (jedi[i].first > min_point)
			jedi[i].first -= min_point;
		else jedi[i].first += m - min_point;
		if (jedi[i].second > min_point)
			jedi[i].second -= min_point;
		else jedi[i].second += m - min_point;

		if (a <= b && a <= min_point && min_point <= b) {
			overlapping.push_back(jedi[i]);
			continue;
		}
		if (a > b && (a <= min_point || min_point <= b)) {
			overlapping.push_back(jedi[i]);
			continue;
		}

		non_overlapping.push_back(jedi[i]);
	}
}

int solve_(int last_point, int end_at) {
	int cnt = 0;
	for (int i = 0; i < non_overlapping.size(); i++) {
		if (non_overlapping[i].first > last_point && 
			non_overlapping[i].second < end_at) {
			cnt++;
			last_point = non_overlapping[i].second;
			//cout << non_overlapping[i].first << ' ' << non_overlapping[i].second << endl;
		}
		/* else {
			cout << non_overlapping[i].first << ' ' << non_overlapping[i].second << " no " << last_point << ' ' << end_at << endl;
		} */
	}
	//cout << cnt << "\n-----------\n";
	return cnt;
}

bool cmp(pair <int, int> j1, pair <int, int> j2) {
	return j1.second < j2.second;
}

void solve() {
    int min_point = get_min_overlaps_point();
    fix_jedis(min_point);

    sort(non_overlapping.begin(), non_overlapping.end(), cmp);
    int sol = solve_(-1, m);
    for (int i = 0; i < overlapping.size(); i++) {
    	// cout << overlapping[i].first << ' ' << overlapping[i].second << endl;
    	sol = max(sol, 1 + solve_(overlapping[i].second % m, overlapping[i].first));
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