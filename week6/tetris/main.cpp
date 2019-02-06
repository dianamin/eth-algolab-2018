#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property <boost::edge_capacity_t, long,
	boost::property <boost::edge_residual_capacity_t, long,
	boost::property <boost::edge_reverse_t, Traits::edge_descriptor > > > > Graph;

typedef boost::property_map <Graph, boost::edge_capacity_t>::type Capacity;
typedef boost::property_map <Graph, boost::edge_residual_capacity_t>::type ResCapacity;
typedef boost::property_map <Graph, boost::edge_reverse_t>::type RevEdge;

typedef boost::graph_traits <Graph>::edge_descriptor Edge;

int w, n;

Graph G;
int s, t;
Capacity capacity_map_;
ResCapacity res_capacity_map_;
RevEdge rev_edge_map_;

void add_edge_(int from, int to, long capacity) {
	Edge e, rev_e; bool success;

	boost::tie(e, success) = boost::add_edge(from, to, G);
	boost::tie(rev_e, success) = boost::add_edge(to, from, G);
	capacity_map_[e] = capacity;
	capacity_map_[rev_e] = 0; // reverse edge has no capacity!
	rev_edge_map_[e] = rev_e;
	rev_edge_map_[rev_e] = e;
}

inline int crack_in(int x) {
	return x;
}

inline int crack_out(int x) {
	return (w + 1) + x;
}

void read() {
	std::cin >> w >> n;

	G = (2 * (w + 1));
	s = crack_out(0);
	t = crack_in(w);

	capacity_map_ = boost::get(boost::edge_capacity, G);
	res_capacity_map_ = boost::get(boost::edge_residual_capacity, G);
	rev_edge_map_ = boost::get(boost::edge_reverse, G);

	for (int i = 1; i < w; i++) {
		add_edge_(crack_in(i), crack_out(i), 1);
	}

	for (int i = 0; i < n; i++) {
		int a, b;
		std::cin >> a >> b;
		if (a > b) std::swap(a, b);
		if (b > w) continue;
		add_edge_(crack_out(a), crack_in(b), 1);
	}
}

void solve() {
	int flow = boost::push_relabel_max_flow(G, s, t);
	std::cout << flow << '\n';
}


int main() {
	std::ios_base::sync_with_stdio(false);

	int t; std::cin >> t;
	while(t--) {
		read();
		solve();
	}

	return 0;
}