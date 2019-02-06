#include <iostream>
#include <vector>

using namespace std;

int n, k, pattern;

vector <int> blocks;

int fix_pattern(int x) {
	int y = 0;
	for (int i = 0, j = k - 1; i < k; i++, j--) {
		if ((x & (1 << i)) == 0) continue;
		y |= (1 << j);
	}
	return y;
}

void output(int x) {
	for (int i = 0; i < k; i++) {
		if (x & (1 << i)) std::cout << 1;
		else std::cout << 0;
		std::cout << ' ';
	}
	std::cout << '\n';
}

void read() {
	cin >> n >> k >> pattern;
	n /= k;
	pattern = fix_pattern(pattern);
	blocks = std::vector <int>(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			int b; cin >> b;
			if (!b) continue;
			blocks[i] |= (1 << j);
		}
	}
}

int negate_pattern(int x) {
	int y = 0;
	for (int i = 0; i < k; i++) {
		if (x & (1 << i)) continue;
		y |= (1 << i);
	}
	return y;
}

bool same(int a, int b) {
	if (a == 0 && b == 0) return true;
	if (a != 0 && b != 0) return true;
	return false;
}

int count_diff(int x, int y) {
	int diff = 0;
	for (int i = 0; i < k; i++) {
		if (!same(x & (1 << i), y & (1 << i)))
			diff++;
	}
	return diff;
}

std::vector <int> dp[2];

void solve() {
	int negated_pattern = negate_pattern(pattern);
	// output(pattern);
	// output(blocks[0]);

	dp[0] = std::vector<int>(n);
	dp[1] = std::vector<int>(n);

	dp[0][0] = count_diff(blocks[0], pattern);
	dp[1][0] = count_diff(blocks[0], negated_pattern);

	dp[0][0] = std::min(dp[0][0], dp[1][0] + 1);
	dp[1][0] = std::min(dp[1][0], dp[0][0] + 1);

	for (int i = 1; i < n; i++) {
		int diff_pattern = count_diff(blocks[i], pattern);
		int diff_negated = count_diff(blocks[i], negated_pattern);

		dp[0][i] = std::min(
			dp[0][i - 1] + diff_pattern,
			dp[1][i - 1] + diff_negated + 1
		);

		dp[1][i] = std::min(
			dp[0][i - 1] + diff_pattern + 1,
			dp[1][i - 1] + diff_negated
		);
	}

	std::cout << dp[0][n - 1] << '\n';
}


int main() {
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while(t--) {
		read();
		solve();
	}
	return 0;
}