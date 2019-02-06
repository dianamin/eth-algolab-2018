#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
long sum;
vector <int> len;

void read() {
	cin >> n;
	len = vector <int>(n);

	sum = 0;
	for (int i = 0; i < n; i++) {
		cin >> len[i];
		sum += len[i];
	}
}


void backtrack(int id, int n, vector < vector <int> > &assignment,
							 vector < vector <int> > &F) {
	if (id >= n) {
		vector <int> t(4, 0);
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < assignment[i].size(); j++)
				t[i] += len[assignment[i][j]];
		F.push_back(t);
		return;
	}

	for (int i = 0; i < 4; i++) {
		assignment[i].push_back(id);
		backtrack(id + 1, n, assignment, F);
		assignment[i].pop_back();
	}
}


void solve() {
	vector < vector <int> > assignment(4);
	vector < vector <int> > F1;
	vector < vector <int> > F2;


	backtrack(0, n / 2, assignment, F1);
	assignment = vector < vector <int> >(4);
	backtrack(n / 2, n, assignment, F2);
	
	sort(F2.begin(), F2.end());

	long long result = 0;

	for (int i = 0; i < F1.size(); i++) {
		std::vector <int> looking_for = F1[i];

		for (int i = 0; i < 4; i++)
			looking_for[i] = sum / 4 - looking_for[i];
		std::pair< vector < vector <int> >::iterator,
				   vector < vector <int> >::iterator > bounds;
		bounds = equal_range(F2.begin(), F2.end(), looking_for);
		result += distance(bounds.first, bounds.second);
	}

	std::cout << result / 24 << '\n';
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