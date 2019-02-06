#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits <
	boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list <
		boost::vecS, boost::vecS, boost::directedS,
		boost::no_property,
		boost::property<boost::edge_capacity_t, long,
		boost::property<boost::edge_residual_capacity_t, long,
		boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > >
	> Graph;

typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type ReverseEdgeMap;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;

class EdgeAdder {
	Graph &G;
	EdgeCapacityMap	&capacitymap;
	ReverseEdgeMap	&revedgemap;

public:
	// to initialize the Object
	EdgeAdder(Graph & G, EdgeCapacityMap &capacitymap, ReverseEdgeMap &revedgemap):
		G(G), capacitymap(capacitymap), revedgemap(revedgemap){}

	// to use the Function (add an edge)
	void addEdge(int from, int to, long capacity) {
		Edge e, rev_e;
		bool success;
		boost::tie(e, success) = boost::add_edge(from, to, G);
		boost::tie(rev_e, success) = boost::add_edge(to, from, G);
		capacitymap[e] = capacity;
		capacitymap[rev_e] = 0; // reverse edge has no capacity!
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};

int n, m;
std::vector <int> needed;
std::vector < std::pair <int, int> > rounds;


void read() {
	std::cin >> n >> m;
	needed = std::vector <int> (n, 0);
	rounds.clear();

	for (int i = 0; i < m; i++) {
		int a, b, c;
		std::cin >> a >> b >> c;
		if (c == 1) needed[a]--;
		else if (c == 2) needed[b]--;
		else rounds.push_back(std::make_pair(a, b));
	}

	for (int i = 0; i < n; i++) {
		int s;
		std::cin >> s;
		needed[i] += s;
	}
}

Graph G;
int s, t;

inline int round(int x) {
	return 1 + x;
}

inline int player(int x) {
	return 1 + rounds.size() + x;
}

void build_graph() {
	G = Graph(1 + rounds.size() + n + 1);

	s = 0;
	t = 1 + rounds.size() + n;

	EdgeCapacityMap capacity_map = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap rev_map = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap res_capacity_map = boost::get(boost::edge_residual_capacity, G);

	EdgeAdder edge_adder(G, capacity_map, rev_map);

	for (int i = 0; i < rounds.size(); i++) {
		edge_adder.addEdge(s, round(i), 1);
		int a = rounds[i].first;
		int b = rounds[i].second;
		edge_adder.addEdge(round(i), player(a), 1);
		edge_adder.addEdge(round(i), player(b), 1);
	}

	for (int i = 0; i < n; i++) {
		edge_adder.addEdge(player(i), t, needed[i]);
	}
}

void solve() {
	for (int i = 0; i < n; i++)
		if (needed[i] < 0) {
			std::cout << "no\n";
			return;
		}

	int expected = 0;
	for (int i = 0; i < n; i++) expected += needed[i];

	if (expected != rounds.size()) {
		std::cout << "no\n";
		return;
	}

	build_graph();

	int flow = boost::push_relabel_max_flow(G, s, t);

	//std::cout << flow << ' ' << expected << ' ';

	if (flow == expected) std::cout << "yes\n";
	else std::cout << "no\n";
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