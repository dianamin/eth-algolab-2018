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
		//std :: cout << success << " s ";
		capacitymap[rev_e] = 0; // reverse edge has no capacity!
		revedgemap[e] = rev_e;
		revedgemap[rev_e] = e;
	}
};

int n, m, s, real_s;
Graph G;
int source_, target_;


void read() {
	std::cin >> n >> m >> s;

	std::vector <bool> added(n, false);

	G = Graph(n + 1);
	source_ = 0;
	target_ = n;

	EdgeCapacityMap capacity_map = boost::get(boost::edge_capacity, G);
	ReverseEdgeMap rev_map = boost::get(boost::edge_reverse, G);
	ResidualCapacityMap res_capacity_map = boost::get(boost::edge_residual_capacity, G);

	EdgeAdder edge_adder(G, capacity_map, rev_map);

	real_s = 0;
	for (int i = 0; i < s; i++) {
		int a;
		std::cin >> a;
		if (added[a]) continue;
		added[a] = true;
		real_s++;
		edge_adder.addEdge(a, target_, 1);
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		std::cin >> a >> b;
		edge_adder.addEdge(a, b, 1);
		edge_adder.addEdge(b, a, 1);
	}
}

void solve() {

	int flow = boost::push_relabel_max_flow(G, source_, target_);

	//std::cout << flow << ' ' << expected << ' ';

	if (flow == real_s) std::cout << "yes\n";
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