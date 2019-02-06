#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

typedef boost::graph_traits<Graph>::edge_iterator EdgeIt;

int g, s;

Graph G;


void read() {
	int l;
	std::cin >> g >> s >> l;
	G = Graph(g + s);

	for (int i = 0; i < l; i++) {
		int a, b;
		std::cin >> a >> b;
		Edge e; bool success;

		boost::tie(e, success) = boost::add_edge(a, b + g, G);
	}
}


inline int ground_station(int x) {
	return x;
}

inline int satellite(int x) {
	return g + x;
}

inline bool is_ground_station(int x) {
	return x < g;
}

inline int is_satellite(int x) {
	return x >= g;
}

std::vector <int> mate_map;
std::vector <bool> visited;

void DFS(int v) {
	if (visited[v]) return;
	visited[v] = true;

	if (is_ground_station(v)) {
		for (auto e : boost::make_iterator_range(boost::out_edges(v, G))) {
			int u = boost::target(e, G);
			if (u == mate_map[v]) continue;
			DFS(u);
		}
	}
	else {
		if (mate_map[v] != boost::graph_traits<Graph>::null_vertex())
			DFS(mate_map[v]);
	}
}


void solve() {
	mate_map = std::vector <int>(g + s);
	boost::edmonds_maximum_cardinality_matching(G, &mate_map[0]);

	visited = std::vector <bool>(g + s, false);

	int none = boost::graph_traits<Graph>::null_vertex();
	for (int v = 0; v < g; v++) {
		if (mate_map[v] == boost::graph_traits<Graph>::null_vertex())
			DFS(v);
	}

	std::vector <int> g_;
	std::vector <int> s_;

	for (int v = 0; v < g; v++) {
		if (!visited[v]) g_.push_back(v);
	}

	for (int v = g; v < g + s; v++) {
		if (visited[v]) s_.push_back(v - g);
	}

	std::cout << g_.size() << ' ' << s_.size() << '\n';
	for (int i = 0; i < g_.size(); i++) std::cout << g_[i] << ' ';
	for (int i = 0; i < s_.size(); i++) std::cout << s_[i] << ' ';
	if (g_.size() + s_.size() != 0) std::cout << '\n';
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