#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

int n, q;
int root_id;
vector < vector <int> > graph;

map <string, int> string_to_id;
vector <string> id_to_string;
vector <int> age;

vector < vector < pair <int, int> > > queries;
vector <string> output;

void read() {
	cin >> n >> q;

	graph = vector < vector <int> > (n);
	string_to_id.clear();
	id_to_string = vector <string> (n);
	age = vector <int>(n);
	queries = vector < vector < pair <int, int> > >(n);
	output = vector <string>(q);

	int max_age = -1;
	for (int i = 0; i < n; i++) {
		string name;
		int x;
		cin >> name >> x;
		string_to_id[name] = i;
		id_to_string[i] = name;
		age[i] = x;

		if (max_age < x) {
			max_age = x;
			root_id = i;
		}
	}

	for (int i = 0; i < n - 1; i++) {
		string a, b;
		cin >> a >> b;
		int id_a = string_to_id[a];
		int id_b = string_to_id[b];
		graph[id_b].push_back(id_a);
	}

	for (int i = 0; i < q; i++) {
		string a;
		int x;

		cin >> a >> x;
		int id_a = string_to_id[a];
		queries[id_a].push_back(make_pair(x, i));
	}
}

int crt_poz = 0;
vector <int> path_frum;

vector <bool> visited;

void DFS(int v) {
	int i = 0, j = 0;
	path_frum[crt_poz] = v;
	crt_poz++;
	//cout << crt_poz << endl;

	//int a = path_frum
	//cout << v << ' ';
	//cout << "ajung aici\n";
	//cout << i << ' ';
	
	//cout << crt_poz << endl;
	//cout << ' ' << n << '\n';
	//cout << "!!!!\n";
	//cout << path_frum[0];	
	//cout << age[path_frum[i]] << ' ' << crt_poz << endl;
	//cout << "ajung si aici\n";
	int x = queries[v].size();
	for (j = 0; j < x; j++) {
		while (i < crt_poz && age[path_frum[i]] > queries[v][j].first) { //older
			//cout << j << ": " << i << ' ' << age[path_frum[i]] << ' ' << queries[v][j].first << endl;
			i++;
		}
		if (i < crt_poz)
			output[queries[v][j].second] = id_to_string[path_frum[i]];
		else output[queries[v][j].second] = "?";
	}

	for (vector <int>::iterator next_v = graph[v].begin();
								next_v != graph[v].end();
								next_v++) {
		int v_ = *next_v;
		//cout << v_ << " plec\n";
		//cout << path_frum.size() << ' ';
		DFS(v_);
	}
	//cout << crt_poz << " out" << '\n';
	crt_poz--;
}

bool cmp(pair <int, int> a, pair <int, int> b) {
	return a.first > b.first;
}

void solve() {
	for (int i = 0; i < n; i++)
		sort(queries[i].begin(), queries[i].end(), cmp);
	crt_poz = 0;
	path_frum = vector <int>(n);
	DFS(root_id);
	for (int i = 0; i < q; i++)
		cout << output[i] << ' ';
	cout << '\n';
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