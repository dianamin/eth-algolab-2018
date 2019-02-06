#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
vector <int> v;

void read() {
	cin >> n >> m >> k;
	v = vector<int>(n + 1);
	for (int i = 1; i <= n; i++)
		cin >> v[i]; 
}


vector <int> start_;
void find_sequences() {
	start_ = vector <int>(n + 1, 0);

	int start_crt = 1;
	int sum_crt = 0;
	for (int i = 1; i <= n; i++) {
		sum_crt += v[i];
		while (sum_crt > k) sum_crt -= v[start_crt++];
		if (sum_crt == k) start_[i] = start_crt;
	}
}

vector < vector <int> > dp;
void solve() {
	find_sequences();

	dp = vector < vector <int> >(m + 1, vector <int>(n + 1, 0));

	for (int i = 1; i <= m; i++)
		for (int j = 1; j <= n; j++) {
			dp[i][j] = dp[i][j - 1];
			if (!start_[j]) continue;
			dp[i][j] = max(dp[i][j],
						   dp[i - 1][start_[j] - 1] + j - start_[j] + 1);
		}

	if (dp[m][n] == dp[m - 1][n]) cout << "fail\n";
	else cout << dp[m][n] << '\n';
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