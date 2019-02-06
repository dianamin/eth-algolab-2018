#include <iostream>
#include <vector>

using namespace std;

int n;
vector <int> v;

void read() {
	cin >> n;
	v = vector<int>(n);
	for (int i = 0; i < n; i++)
		cin >> v[i];
}


vector < vector <int> > dp;
void solve() {
	dp = vector < vector <int> >(n, vector <int>(n));

	for (int i = 0; i < n; i++) dp[i][i] = v[i];
	for (int i = 0; i < n - 1; i++) dp[i][i + 1] = max(v[i], v[i + 1]);

	for (int l = 3; l <= n; l++)
		for (int i = 0; i + l - 1 < n; i++) {
			int j = i + l - 1;
			dp[i][j] = max(
				v[i] + min(dp[i + 2][j], dp[i + 1][j - 1]),
				v[j] + min(dp[i][j - 2], dp[i + 1][j - 1])
			);
		}

	cout << dp[0][n - 1] << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while(t--) {
		read();
		solve();
	}
	return 0;
}