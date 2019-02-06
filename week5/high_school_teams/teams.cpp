#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

int n, k;
vector <int> skill;

void print_mask(int mask) {
	for (int i = 0; i < n; i++)
		cout << ((mask & (1 << i)) != 0);
	cout << endl;
}

void read() {
	cin >> n >> k;
	skill = vector <int>(n);
	for (int i = 0; i < n; i++) cin >> skill[i];
}

void solve() {
	int n1 = (n + 1) / 2;
	int n2 = n - n1;

	map < pair < pair <long long, long long>, long long >, long long > pairs;
	vector <int> selected;

	for (int mask = 0; mask < (1 << n1); mask++) {
		selected.clear();
		for (int player = 0; player < n1; player++)
			if ((mask & (1 << player)) != 0)
				selected.push_back(skill[player]);
		for (int mask2 = 0; mask2 < (1 << selected.size()); mask2++) {
			long long sum1 = 0;
			long long sum2 = 0;
			for (int player = 0; player < selected.size(); player++) {
				if (mask2 & (1 << player)) sum1 += selected[player];
				else sum2 += selected[player];
			}
			pair < pair <long long, long long>, long long > new_pair;
			new_pair = make_pair(make_pair(sum1, sum2), selected.size());
			if (pairs.count(new_pair) == 0) pairs[new_pair] = 0;
			pairs[new_pair]++;
		}
	}

	map <long long, vector < pair <long long, long long> > > final_pairs;

	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		long long sum1 = it->first.first.first;
		long long sum2 = it->first.first.second;
		long long score_needed = sum1 - sum2;
		long long assigned = it->first.second;
		long long count = it->second;

		final_pairs[score_needed].push_back(make_pair(assigned, count));
	}

	long long sol = 0;
	for (int mask = 0; mask < (1 << n2); mask++) {
		selected.clear();
		for (int player = 0; player < n2; player++)
			if ((mask & (1 << player)) != 0)
				selected.push_back(skill[n1 + player]);
		for (int mask2 = 0; mask2 < (1 << selected.size()); mask2++) {
			long long sum1 = 0;
			long long sum2 = 0;
			for (int player = 0; player < selected.size(); player++) {
				if ((mask2 & (1 << player))) sum1 += selected[player];
				else sum2 += selected[player];
			}


			long long skill_diff = sum2 - sum1;
			if (final_pairs.count(skill_diff)) {
				vector < pair <long long, long long> > options = final_pairs[skill_diff];
				for (auto it = options.begin(); it != options.end(); it++) {
					long long assigned = it->first + selected.size();
					if (assigned >= n - k)
						sol += it->second;
				}
			}
		}
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