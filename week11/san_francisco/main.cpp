#include <iostream>
#include <vector>

using namespace std;

int n, m;
long long x;
int K;

vector < vector <int> > N;
vector < vector <long long> > W;

void read() {
	cin >> n >> m >> x >> K;
	N = vector < vector <int> >(n);
	W = vector < vector <long long> >(n);

	for (int i = 0; i < m; i++) {
		int v, u; long long w;
		cin >> v >> u >> w;
		N[v].push_back(u);
		W[v].push_back(w);
	}
}

vector < vector <long long> > dp;

long long max_neighbor(int v, int k) {
	long long max_ = -1;
	for (int i = 0; i < N[v].size(); i++) {
		int u = N[v][i];
		long long w = W[v][i];
		max_ = max(max_, w + dp[k - 1][u]);
	}
	return max_;
}

void solve() {
	dp = vector < vector <long long> >(K + 1, vector <long long> (n, 0));

	for (int k = 1; k <= K; k++) {
		dp[k][0] = max_neighbor(0, k);

		for (int v = 1; v < n; v++) {
			if (N[v].empty()) dp[k][v] = dp[k][0];
			else dp[k][v] = max_neighbor(v, k);
		}
	}

	if (dp[K][0] < x) {
		cout << "Impossible\n";
		return;
	}
	for (int k = 0; k <= K; k++) 
		if (dp[k][0] >= x) {
			cout << k << '\n';
			return;
		}
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