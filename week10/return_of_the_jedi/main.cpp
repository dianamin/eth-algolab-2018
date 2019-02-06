#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>

typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::undirectedS,
	boost::no_property,
	boost::property<boost::edge_weight_t, long>
	> Graph;

typedef boost::property_map <Graph, boost::edge_weight_t>::type WeightMap;

typedef Graph::edge_descriptor Edge;
typedef Graph::vertex_descriptor Vertex;


typedef Graph::edge_iterator Edge_it;

int n, s;

Graph g;
WeightMap weight_map_;


std::vector < std::vector <int> > dist;

std::vector < std::vector <Edge> > edge_;

void read() {
	std::cin >> n >> s;
	s--;
	dist = std::vector < std::vector <int> >(n - 1);

    for (int j = 1; j <= n - 1; ++j) {
		for (int k = 1; k <= n - j; ++k) {
			int cost;
			std::cin >> cost;
			dist[j - 1].push_back(cost);
		}
    }
}

std::vector <Edge> to_add;
void build_graph() {
	g = Graph(n);

	weight_map_ = boost::get(boost::edge_weight, g);
	edge_ = std::vector < std::vector <Edge> >(n, std::vector <Edge>(n));

	for (int j = 0; j < n - 1; j++)
		for (int k = 0; k < n - j - 1; k++) {
			Edge e; bool success;
			tie(e, success) = boost::add_edge(j, j + k + 1, g);
			assert(success);
			weight_map_[e] = dist[j][k];
			edge_[j][j + k + 1] = edge_[j + k + 1][j] = e;
		}
}



std::vector <Vertex> p;
std::vector < std::vector <int> > max_d;
std::vector < std::vector <int> > tree;


std::vector <int> path;

std::vector <int> lin;
int ind;
std::vector <int> tag;
std::vector <int> tag_for;
std::vector <int> first;


long long total = 0;

void DFS(int v, int last_d) {
	std::vector <int>::iterator it;
	max_d[v][v] = 0;
	for (it = path.begin(); it != path.end(); it++) {
		max_d[*it][v] = std::max(max_d[*it][p[v]], last_d);
	}
	path.push_back(v);

	tag[v] = ind++;
	tag_for[tag[v]] = v;
	first[v] = lin.size();
	lin.push_back(tag[v]);

	for (it = tree[v].begin(); it != tree[v].end(); it++) {
		int u = *it;

		Edge e; bool success;
		e = edge_[u][v];


		int d = weight_map_[e];
		//int d = 1;
		DFS(u, d);
		lin.push_back(tag[v]);
	}
	path.pop_back();
}

std::vector < std::vector <int> > rmq;

std::vector <int> log2_;

void build_rmq() {
	int len = 1;
	int elems = lin.size();
	log2_ = std::vector <int>(elems);

	for (int i = 2; i < elems; i++) log2_[i] = log2_[i / 2] + 1;
	while ((1 << len) <= elems) len++;
	rmq = std::vector < std::vector <int> > (len + 1, std::vector <int>(elems));

	for (int i = 0; i < elems; i++)
		rmq[0][i] = lin[i];
	for (int l = 1; l < len; l++) {
		int jump = (1 << (l - 1));
		for (int i = 0; i < elems - jump && i + jump < elems; i++) {
			rmq[l][i] = std::min(rmq[l - 1][i], rmq[l - 1][i + jump]);
		}
	}

}

int get_lca(int a, int b) {
	int lca, l;
    a = first[a];
    b = first[b];
    if (a > b) std::swap(a, b);
    l = log2_[b - a + 1];
    lca = std::min(rmq[l][a], rmq[l][b - (1 << l) + 1]);
    return tag_for[lca]; 
}

void solve() {
	build_graph();
	p = std::vector <Vertex>(n);
	max_d = std::vector < std::vector <int> >(n, std::vector <int>(n));
  	prim_minimum_spanning_tree(g, &p[0], boost::root_vertex(s));

  	total = 0;
  	path.clear();
  	tree = std::vector < std::vector <int> >(n);
  	for (int i = 0; i < n; i++) 
  		if (p[i] != i) {
  			tree[p[i]].push_back(i);
  			Edge e = edge_[i][p[i]];
			total += weight_map_[e];
  		}

  	tag = std::vector<int>(n + 1);
  	tag_for = std::vector<int>(n + 1);
  	first = std::vector <int>(n + 1);
  	lin.clear();
  	ind = 1;
  	DFS(s, 0);

  	build_rmq();	

  	long long min_weight = total + INT_MAX;

  	for (int u = 0; u < n; u++)
	for (int v = u + 1; v < n; v++) {
		Edge e; bool success;
		if (p[u] == v || p[v] == u) continue;
		e = edge_[u][v];
  		long long w = total + weight_map_[e];
  		int ca = get_lca(u, v);
		w -= std::max(max_d[ca][u], max_d[ca][v]); 
  		min_weight = std::min(w, min_weight);
  	}
  	std::cout << min_weight << '\n';
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