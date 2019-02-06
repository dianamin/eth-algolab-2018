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

void add_edge_(int a, int b, long c, long w_) {
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
}

int n, m, s;
long max_b;
int source_, target_;

std::vector < std::vector <long> > b;

inline int buyer(int i) {
	return 1 + i;
}

inline int site(int i) {
	return 1 + n + i;
}

inline int state(int i) {
	return 1 + n + m + i;
}


void read() {
	std::cin >> n >> m >> s;

	G = Graph(1 + n + m + s + 1);
	source_ = 0; target_ = 1 + n + m + s;

	b = std::vector < std::vector <long> >(n, std::vector <long>(m));

	for (int i = 0; i < n; i++)
		add_edge_(source_, buyer(i), 1, 0);

	for (int i = 0; i < s; i++) {
		int l; std::cin >> l;
		add_edge_(state(i), target_, l, 0);
	}

	for (int i = 0; i < m; i++) {
		int s_; std::cin >> s_;
		add_edge_(site(i), state(s_ - 1), 1, 0);
	}

	max_b = -1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			std::cin >> b[i][j];
			max_b = std::max(b[i][j], max_b);
		}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			add_edge_(buyer(i), site(j), 1, max_b - b[i][j]);
}

void solve() {
	boost::successive_shortest_path_nonnegative_weights(G, source_, target_);
	long cost = boost::find_flow_cost(G);
	long flow = 0;

	for (auto e: boost::make_iterator_range(boost::out_edges(source_, G))) {
		flow += cap[e] - res[e];
	}

	std::cout << flow << ' ' << max_b * flow - cost << '\n';
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