#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int n, k, m;

vector <double> p;

void read() {
	cin >> n >> k >> m;
	p = vector <double>(n);
	for (int i = 0; i < n; i++)
		cin >> p[i];
}

vector < vector <double> > dp;

void solve() {
	dp = vector < vector <double> >(n + 1, vector <double>(m + 1));

	dp[n][m] = 1;

	for (int i = n - 1; i >= 0; i--)
		for (int k = 0; k <= m; k++) {
			double dp_try = 0;
			for (int b = 1; b <= k; b++)
				dp_try = max(dp_try,
							 dp[i + 1][min(m, k + b)] * p[i] +
							 dp[i + 1][k - b] * (1 - p[i]));
			dp[i][k] =  max(dp_try, dp[i + 1][k]);
		}

	cout << dp[0][k] << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	std::cout << fixed << setprecision(5);
	int t;
	cin >> t;
	while(t--) {
		read();
		solve();
	}
	return 0;
}