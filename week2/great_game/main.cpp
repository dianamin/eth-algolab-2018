#include <iostream>
#include <vector>

using namespace std;

const int INF = (1 << 13);

int n, m;
int poz_a, poz_b;
vector < vector <int> > N;

void read() {
	cin >> n >> m;
	cin >> poz_a >> poz_b;
	poz_a--;
	poz_b--;

	N = vector < vector <int> >(n);

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		N[u].push_back(v);
	}
}

vector < vector <int> > dp;


void solve() {
	dp = vector < vector <int> >(n, vector <int>(2));

	dp[n - 1][0] = dp[n - 1][1] = 0;

	for (int v = n - 2; v >= 0; v--) {
		int min_next = INF;
		int max_next = -INF;
		vector <int>::iterator u;
		for (u = N[v].begin(); u != N[v].end(); u++) {
			min_next = min(min_next, dp[*u][1]);
			max_next = max(max_next, dp[*u][0]);
		}
		dp[v][0] = 1 + min_next;
		dp[v][1] = 1 + max_next;
	}

	int steps_a = dp[poz_a][0];
	int steps_b = dp[poz_b][0];

	if (steps_a < steps_b ||
	   (steps_a == steps_b && steps_a % 2 == 1)) {
		cout << 0;
	}
	else cout << 1;
	cout << '\n';
}


int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--) {
		read();
		solve();
	}
	return 0;
}