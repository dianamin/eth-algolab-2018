#include <iostream>
#include <vector>

using namespace std;

int n, k;

vector <int> cost;
vector <int> vol;

void read() {
	cin >> n >> k;

	cost = vector <int>(n + 1);
	vol = vector <int>(n + 1);

	for (int i = 1; i <= n; i++)
		cin >> cost[i] >> vol[i];
}

vector < vector <int> > dp;
vector < vector <int> > cnt;
vector <bool> updated_here;

void solve() {
	dp = vector < vector <int> >(n + 1, vector <int>(k + 1));
	cnt = vector < vector <int> >(n + 1, vector <int>(k + 1));
	updated_here = vector<bool>(k + 1, false);

	int quant = 1;
	dp[1][0] = 0;
	cnt[1][0] = 0;
	for (int v = 1; v <= k; v++) {
		dp[1][v] = cost[1] * quant;
		cnt[1][v] = 1;
		if (v % vol[1] == 0) quant++;
	}

	for (int bev = 2; bev <= n; bev++) {
		for (int v = 0; v <= k; v++) {
			dp[bev][v] = dp[bev - 1][v];
			cnt[bev][v] = cnt[bev - 1][v];
			updated_here[v] = false;
		}

		for (int v = 1; v <= min(k, vol[bev]); v++) {
			if (dp[bev][v] > cost[bev]) {
				dp[bev][v] = cost[bev];
				cnt[bev][v] = 1;
				updated_here[v] = true;
			}
		}
		
		for (int v = vol[bev] + 1; v <= k; v++) {
			int old_v = v - vol[bev];
			int new_cost = dp[bev][old_v] + cost[bev];

			int new_cnt = cnt[bev][old_v];
			if (!updated_here[old_v]) new_cnt++;

			// cout << new_cnt << ' ';

			if (new_cost < dp[bev][v]) {
				dp[bev][v] = new_cost;
				updated_here[v] = true;
				cnt[bev][v] = new_cnt;
			}
			else if (new_cost == dp[bev][v] &&
					 new_cnt  > cnt[bev][v]) {
				cnt[bev][v] = new_cnt;
				updated_here[v] = true;
			}
			// cout << cnt[bev][new_vol] << ' ' << new_vol << ' ' << k << '\n';
		}
	}

	std::cout << dp[n][k] << ' ' << cnt[n][k] << '\n';
}


int main() {
	std::ios_base::sync_with_stdio(false);
	int t;

	std::cin >> t;
	while(t--) {
		read();
		solve();
	}

	return 0;
}