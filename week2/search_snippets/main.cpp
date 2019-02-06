#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace std;

int n;

vector <int> m;
set <int> positions;
map <int, int> word_at;

void read() {
	cin >> n;
	m = std::vector <int>(n);
	for (int i = 0; i < n; i++) cin >> m[i];

	positions.clear();
	word_at.clear();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m[i]; j++) {
			int pos;
			cin >> pos;
			positions.insert(pos);
			word_at[pos] = i;
		}
}

vector <int> occs;

void solve() {
	int found_cnt = 0;
	int sol = (1 << 30); // max pos
	occs = vector <int>(n, 0);
	
	set <int> :: iterator pos;
	set <int> :: iterator last_pos = positions.begin();

	for (pos = positions.begin(); pos != positions.end(); pos++) {
		occs[word_at[*pos]]++;
		if (occs[word_at[*pos]] == 1) found_cnt++;

		if (found_cnt == n) {
			while (last_pos != pos && occs[word_at[*last_pos]] > 1) {
				occs[word_at[*last_pos]]--;
				last_pos++;
			}
			sol = min(sol, *pos - *last_pos + 1);
		}
	}

	std::cout << sol << '\n';
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