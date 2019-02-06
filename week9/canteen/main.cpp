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
int source_, target_;
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

int n;

std::vector <int> a, c, s, p, v, e;

void read() {
	std::cin >> n;

	a = std::vector <int>(n);
	c = std::vector <int>(n);
	s = std::vector <int>(n);
	p = std::vector <int>(n);
	v = std::vector <int>(n - 1);
	e = std::vector <int>(n - 1);

	for (int i = 0; i < n; i++) {
		std::cin >> a[i] >> c[i];
	}

	for (int i = 0; i < n; i++) {
		std::cin >> s[i] >> p[i];
	}

	for (int i = 0; i < n - 1; i++) {
		std::cin >> v[i] >> e[i];
	}
}

int max_p, students;

void build_graph() {
	G = Graph(1 + n + 1);
	source_ = n;
	target_ = n + 1;


	cap = boost::get(boost::edge_capacity, G);
	res = boost::get(boost::edge_residual_capacity, G);
	rev = boost::get(boost::edge_reverse, G);
	w = boost::get(boost::edge_weight, G);

	max_p = 0;
	students = 0;
	for (int i = 0; i < n; i++) {
		max_p = std::max(max_p, p[i]);
		students += s[i];
	}

	for (int i = 0; i < n; i++) {
		add_edge_(source_, i, a[i], c[i]);
		add_edge_(i, target_, s[i], max_p - p[i]);
	}

	for (int i = 0; i < n - 1; i++) {
		add_edge_(i, i + 1, v[i], e[i]);
	}
}

void solve() {
	build_graph();
	boost::successive_shortest_path_nonnegative_weights(G, source_, target_);
	long cost = boost::find_flow_cost(G);
	long flow = 0;

	for (auto e: boost::make_iterator_range(boost::out_edges(source_, G))) {
		flow += cap[e] - res[e];
	}

	if (flow == students) std::cout << "possible ";
	else std::cout << "impossible ";
	std::cout << flow << ' ' << max_p * flow - cost << '\n';
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