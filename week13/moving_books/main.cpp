#include <iostream>
#include <algorithm>
#include <set>
#include <vector>

int n, m;
std::vector<int> s;
std::vector<int> w;

void read() {
	std::cin >> n >> m;
	s = std::vector<int>(n);
	w = std::vector<int>(m);
	for (int i = 0; i < n; i++) std::cin >> s[i];
	for (int i = 0; i < m; i++) std::cin >> w[i];
}

inline bool comp(int a, int b) {
	return a > b;
}

void solve() {
	std::sort(s.begin(), s.end(), comp);
	
	std::multiset <int> w_set;

	int heaviest = -1;
	for (int i = 0; i < m; i++) {
		w_set.insert(-w[i]);
		heaviest = std::max(heaviest, w[i]);
	}

	if (heaviest > s[0]) {
		std::cout << "impossible\n";
		return;
	}

	int rounds_count = 0;
	while(!w_set.empty()) {
		rounds_count++;
		for (int i = 0; i < n; i++) {
			//std::cout << i << ": ";
			std::multiset <int> :: iterator it;
			it = w_set.lower_bound(-s[i]);
			//std::cout << *it << '\n';
			if (it == w_set.end()) break;
			w_set.erase(it);
		}
	}

	std::cout << 3 * rounds_count - 1 << '\n';
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