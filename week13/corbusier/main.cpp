#include <iostream>
#include <vector>

using namespace std;

int n, i, k;
vector <int> h;

void read() {
	cin >> n >> i >> k;
	h = vector <int>(n);
	for (int disk = 0; disk < n; disk++)
		cin >> h[disk];
}

void solve() {
	vector < vector <bool> > can_obtain;
	can_obtain = vector < vector <bool> >(n, vector <bool>(k, false));

	can_obtain[0][h[0] % k] = true;

	for (int disk = 1; disk < n; disk++) { 
		can_obtain[disk][h[disk] % k] = true;

		for (int possible_h = 0; possible_h < k; possible_h++) {
			if (!can_obtain[disk - 1][possible_h]) continue;

			can_obtain[disk][possible_h] = true;
			can_obtain[disk][(possible_h + h[disk]) % k] = true;
		}
	}

	if (can_obtain[n - 1][i]) cout << "yes\n";
	else cout << "no\n";
}


int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--) {
		read();
		solve();
	}
}