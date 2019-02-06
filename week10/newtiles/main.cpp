#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cassert>
#include <bitset>

using namespace std;

int h, w;
const int W = 17;


void solve() {
	int h, w;
	cin >> h >> w;
	vector< bitset <W> > tiles = vector< bitset <W> > (h);

	int b;
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			cin >> b;
			if (i == 0 || i == h - 1) continue;
			if (j == 0 || j == w - 1) continue;
			if (!b) tiles[i - 1].set(j - 1);
		}
	}
	h = h - 2;
	w = w - 2;
	// cout << h << ' ' << w << endl;
	if (h <= 1 || w <= 1) {
		cout << 0 << endl;
		return;
	}

	vector < vector <int> > dp = vector < vector <int> >(h, vector <int> (1 << w));
	auto ALL = bitset<W>((1<<w)-1);

	for (int i = 1; i < h; ++i) {
		for (int num_blocked = w; num_blocked >= 0; num_blocked--)
		for (int s_ = 0; s_ < (1 << w); s_++) {
			int sol = -1;

			auto s = bitset<W>(s_);
			if (s.count != num_blocked) continue;

			int n_tiles = 0;
			for (int j = 0; j < w - 1; ) {
				if (!s.test(j) && !s.test(j + 1) &&
					!tiles[i][j] && !tiles[i][j + 1] &&
					!tiles[i - 1][j] && !tiles[i - 1][j + 1]) {
					n_tiles++;
					j += 2;
				}
				else j++;
			}

			auto s_flipped = ALL xor s;
			sol = n_tiles + dp[i - 1][s_flipped.to_ulong()];
			for (int j = 0; j < w; j++) {
				if (s.test(j)) continue;
				auto s_ = s;
				s_.flip(j);
				sol = max(sol, dp[i][s_.to_ulong()]);
			}
			dp[i][s.to_ulong()] = sol;
		}
	}

	cout << dp[h - 1][0] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
    	solve();
    }
    return 0;
}