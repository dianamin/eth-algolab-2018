#include <iostream>
#include <vector>


int n, m, k;
std::vector <int> strength;

std::vector <int> first;
std::vector < std::vector <int> > dp;
std::vector < std::vector <int> > dp_ints;

void read() {
	std::cin >> n >> m >> k;

	strength = std::vector <int>(n + 1);
	for (int i = 1; i <= n; i++)
		std::cin >> strength[i];
}

void find_intervals() {
	first = std::vector <int>(n + 1, 0);

	int f_poz = 1;
	int s = 0;
	for (int poz = 1; poz <= n; poz++) {
		s += strength[poz];
		while (s > k && f_poz <= poz) {
			s -= strength[f_poz];
			f_poz++;
		}
		if (s == k) first[poz] = f_poz;
	}
}

void solve() {
	find_intervals();
	dp = std::vector < std::vector <int> >(m + 1, std::vector <int> (n + 1));
	dp_ints = std::vector < std::vector <int> >(m + 1, std::vector <int> (n + 1));
	// dp[#atacatori][pozitie]

	//init
	dp[1][0] = 0;
	dp_ints[1][0] = 0;
	for (int poz = 1; poz <= n; poz++) {
		dp[1][poz] = dp[1][poz - 1];
		dp_ints[1][poz] = dp_ints[1][poz - 1];
		if (!first[poz]) continue;
		dp[1][poz] = std::max(dp[1][poz], poz - first[poz] + 1);
		dp_ints[1][poz] = 1;
	}

	for (int attackers = 2; attackers <= m; attackers++) {
		dp[attackers][0] = 0;
		dp_ints[attackers][0] = 0;
		for (int poz = 1; poz <= n; poz++) {
			dp[attackers][poz] = dp[attackers][poz - 1];
			dp_ints[attackers][poz] = dp_ints[attackers][poz - 1];
			if (!first[poz]) continue;

			int x = dp[attackers - 1][first[poz] - 1] + poz - first[poz] + 1;
			if (x >= dp[attackers][poz]) {
				dp[attackers][poz] = x;
				dp_ints[attackers][poz] = dp_ints[attackers - 1][first[poz] - 1] + 1;
			}
		}
	}

	if (dp_ints[m][n] != m) std::cout << "fail\n";
	else std::cout << dp[m][n] << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t;

	std::cin >> t;
	while (t--) {
		read();
		solve();
	}

	return 0;
}