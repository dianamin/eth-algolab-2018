#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector <int> parasols;

void read() {
	cin >> n;
	parasols = vector <int>(n);
	for (int i = 0; i < n; i++) {
		cin >> parasols[i];
	}
}


vector <int> furthest_left;
vector <int> furthest_right;

int scaled_by;


void fix_parasols() {
	int min_p = -1;
	std::sort(parasols.begin(), parasols.end());
	for (int i = 0; i < n; i++)
		min_p = min(parasols[i], min_p);
	scaled_by = abs(min_p);
	for (int i = 0; i < n; i++)
		parasols[i] += scaled_by;

}

void solve() {
	if (n == 1) {
		cout << 1 << ' ' << 0 << ' ' << '\n' << 0 << '\n';
		return;
	}

	fix_parasols();
	int min_p = parasols[0];
	int max_p = parasols[n - 1];
	furthest_left = vector <int>(max_p + 1);
	furthest_right = vector <int>(max_p + 1);

	furthest_left[min_p] = 0;
	int last_left = 0;
	for (int p = min_p; p <= max_p; p++) {
		if (p - parasols[last_left] > 100) last_left++;
		furthest_left[p] = last_left;
	}

	furthest_right[max_p] = n - 1;
	int last_right = n - 1;

	for (int p = max_p; p >= min_p; p--) {
		if(parasols[last_right] - p > 100) last_right--;
		furthest_right[p] = last_right;
	}

	int max_parasols = -1;
	int min_d;
	vector <int> sol;

	for (int p = min_p; p <= max_p; p++) {
		int d_crt = max(parasols[furthest_right[p]] - p,
						p - parasols[furthest_left[p]]);
		int par_crt = furthest_right[p] - furthest_left[p] + 1;
		//cout << parasols[furthest_right[p]] << ' ' << furthest_left[p] << ' ' << p << endl;
		//cout << par_crt << ' ';
		if (max_parasols < par_crt) {
			sol.clear();
			sol.push_back(p);
			min_d = d_crt;
			max_parasols = par_crt;
			continue;
		}
		if (max_parasols == par_crt) {
			if (min_d < d_crt) continue;
			if (min_d == d_crt) {
				sol.push_back(p);
				continue;
			}
			min_d = d_crt;
			sol.clear();
			sol.push_back(p);
		}
	}

	std::cout << max_parasols << ' ' << min_d << '\n';
	for (int i = 0; i < sol.size(); i++) {
		std::cout << sol[i] - scaled_by << ' ';
	}
	std::cout << '\n';
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