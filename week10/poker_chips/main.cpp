#include <iostream>
#include <vector>

using namespace std;

int n;
vector <int> m;
vector < vector <int> > stacks;

vector <int> conf;

void read() {
	cin >> n;
	m = vector <int>(5, 0);
	stacks = vector < vector <int> >(5);

	conf = vector <int>(5);

	for (int i = 0; i < n; i++) cin >> m[i];

	for (int i = 0; i < n; i++) {
		conf[i] = m[i];
		stacks[i] = vector <int>(m[i]);
		for (int j = 0; j < m[i]; j++) {
			cin >> stacks[i][j];
		}
	}
}

vector < vector < vector < vector < vector <int> > > > > dp;

int solve_dp(vector <int> &conf) {
	if (dp[conf[0]][conf[1]][conf[2]][conf[3]][conf[4]] != -1)
		return dp[conf[0]][conf[1]][conf[2]][conf[3]][conf[4]];

	int max_score = -1;
	for (int set = 1; set < 32; set++) {
		int color = -1;
		int set_size = 0;
		bool valid = true;

		vector <int> next_conf(5);
		
			//cout << m[0] << ' ' << m[1] << ' ' << set << ' ';
		for (int i = 0; i < 5; i++) {
			if ((set & (1 << i)) != 0) {
				if (conf[i] == 0) {
					valid = false;
					break;
				}

				if (color == -1) color = stacks[i][conf[i] - 1];
				else if (color != stacks[i][conf[i] - 1]) {
					valid = false;
					break;
				}

				set_size++;
				next_conf[i] = conf[i] - 1;
			}
			else next_conf[i] = conf[i];
		}

//		cout << valid << endl;

		if (!valid) continue;
//		cout << set_size << ' ' << set << endl;
		int score = solve_dp(next_conf);
		if (set_size > 1) score += 1 << (set_size - 2);

		max_score = max(score, max_score);
	}


	dp[conf[0]][conf[1]][conf[2]][conf[3]][conf[4]] = max_score;
	return max_score;
}


void solve() {
	dp = 
		vector < vector < vector < vector < vector <int> > > > >(
			1 + m[0], vector < vector < vector < vector <int> > > >(
				1 + m[1], vector < vector < vector <int> > >(
					1 + m[2], vector < vector <int> >(
						1 + m[3], vector <int> (
							1 + m[4], -1
						)
					)
				)
			)
		);

	dp[0][0][0][0][0] = 0;

	cout << solve_dp(conf) << '\n';
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