#include <iostream>
#include <vector>

using namespace std;

int n, m, k;
long long x;

vector < vector <int> > graph;
vector < vector <long long> > score;



void read() {
	cin >> n >> m >> x >> k;

	graph = vector < vector <int> >(n);
	score = vector < vector <long long> >(n);

	for (int i = 0; i < m; i++) {
		int u, v, p;
		cin >> u >> v >> p;
		graph[u].push_back(v);
		score[u].push_back(p);
	}
}

void solve() {
	vector < vector <long long> > dp(k + 1, vector <long long> (n));

	for (int v = 0; v < n; v++)
		dp[0][v] = 0;

	for (int move = 1; move <= k; move++) {
		for (int v = 0; v < n; v++) {
			if (graph[v].empty()) {
				dp[move][v] = dp[move][0]; // free move
				continue;
			}
			long long max_neighbors = -1;
			for (int i = 0; i < graph[v].size(); i++) {
				int u = graph[v][i];
				long long w_u = score[v][i];
				max_neighbors = max(dp[move - 1][u] + w_u, max_neighbors);
			}
			dp[move][v] = max_neighbors;
		}

		// cout << move << ' ' << dp[move][0] << ' ' << x << endl;
		if (dp[move][0] >= x) {
			cout << move << '\n';
			return;
		}
	}

	cout << "Impossible\n";
}

int main() {
	ios_base::sync_with_stdio(false);

	int t; cin >> t;
	while(t--) {
		read();
		solve();
	}
}

