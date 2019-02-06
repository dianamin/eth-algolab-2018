#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property <boost::edge_capacity_t, long,
	boost::property <boost::edge_residual_capacity_t, long,
	boost::property <boost::edge_reverse_t, Traits::edge_descriptor,
	boost::property <boost::edge_weight_t, long> > > > > Graph;

typedef boost::graph_traits <Graph>::edge_descriptor Edge;

typedef boost::property_map <Graph, boost::edge_capacity_t>::type CapacityMap;
typedef boost::property_map <Graph, boost::edge_residual_capacity_t>::type ResCapacityMap;
typedef boost::property_map <Graph, boost::edge_reverse_t>::type ReverseMap;
typedef boost::property_map <Graph, boost::edge_weight_t>::type WeightMap;

Graph G;
CapacityMap cap;
ResCapacityMap res;
ReverseMap rev;
WeightMap w;

Edge add_edge_(int a, int b, long c, long w_) {
	Edge e, rev_e;
	bool s;

	boost::tie(e, s) = boost::add_edge(a, b, G);
	boost::tie(rev_e, s) = boost::add_edge(b, a, G);

	cap[e] = c;
	cap[rev_e] = 0;

	w[e] = w_;
	w[rev_e] = -w_;

	rev[e] = rev_e;
	rev[rev_e] = e;

	return e;
}

int n, m, b, s, t;
int s_;

void read() {
	std::cin >> n >> m >> b >> s >> t;

	G = Graph(n + 1);
	cap = boost::get(boost::edge_capacity, G);
	res = boost::get(boost::edge_residual_capacity, G);
	rev = boost::get(boost::edge_reverse, G);
	w = boost::get(boost::edge_weight, G);
	s_ = n;

	for (int i = 0; i < m; i++) {
		int a, b, d, e;
		std::cin >> a >> b >> d >> e; 
		add_edge_(a, b, e, d);
	}
}

void solve() {
	boost::successive_shortest_path_nonnegative_weights(G, s, t);
	long flow = 0;

	for (auto e: boost::make_iterator_range(boost::out_edges(s, G))) {
		flow += cap[e] - res[e];
	}

	int st = 1, dr = flow, sol = 0;

	Edge e = add_edge_(s_, s, 0, 0);
	while (st <= dr) {
		int mid = (st + dr) / 2;
		cap[e] = mid;
		boost::successive_shortest_path_nonnegative_weights(G, s_, t);
		long cost = boost::find_flow_cost(G);
		if (cost <= b) {
			sol = mid;
			st = mid + 1;
		}
		else dr = mid - 1;
	}

	std::cout << sol << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t;
	std::cin >> t;
	while(t--) {
		read();
		solve();
	}
}