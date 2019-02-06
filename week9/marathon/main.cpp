#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property <boost::edge_capacity_t, long,
	boost::property <boost::edge_residual_capacity_t, long,
	boost::property <boost::edge_reverse_t, Traits::edge_descriptor,
	boost::property <boost::edge_weight_t, long> > > > > Graph;


typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property <boost::edge_weight_t, long> > DiGraph;

typedef boost::graph_traits <Graph>::edge_descriptor Edge;
typedef boost::graph_traits <DiGraph>::edge_descriptor DiEdge;

typedef boost::property_map <Graph, boost::edge_capacity_t>::type CapacityMap;
typedef boost::property_map <Graph, boost::edge_residual_capacity_t>::type ResCapacityMap;
typedef boost::property_map <Graph, boost::edge_reverse_t>::type ReverseMap;
typedef boost::property_map <Graph, boost::edge_weight_t>::type WeightMap;
typedef boost::property_map <DiGraph, boost::edge_weight_t>::type DiWeightMap;

Graph G;
DiGraph DiG;
CapacityMap cap;
ResCapacityMap res;
ReverseMap rev;
WeightMap w;
DiWeightMap diw;

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

int n, m, s, f, s_;

void read() {
	std::cin >> n >> m >> s >> f;

	G = Graph(n + 1);
	s_ = n;

	cap = boost::get(boost::edge_capacity, G);
	res = boost::get(boost::edge_residual_capacity, G);
	rev = boost::get(boost::edge_reverse, G);
	w = boost::get(boost::edge_weight, G);

	DiG = DiGraph(n);
	diw = boost::get(boost::edge_weight, DiG);

	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		std::cin >> a >> b >> c >> d;
		if (a == b) continue;
		add_edge_(a, b, c, d);
		add_edge_(b, a, c, d);

		DiEdge e; bool succ;
		boost::tie(e, succ) = boost::add_edge(a, b, DiG);
		diw[e] = d;
		boost::tie(e, succ) = boost::add_edge(b, a, DiG);
		diw[e] = d;
	}
}

long expected_d;

bool flows(long flow) {
	boost::successive_shortest_path_nonnegative_weights(G, s_, f);
	long cost = boost::find_flow_cost(G);

	return (cost == expected_d * flow);
}


void solve() {
	std::vector <long> d = std::vector <long>(n);
	dijkstra_shortest_paths(DiG, s,
          distance_map(make_iterator_property_map(d.begin(),
                                                  get(boost::vertex_index, DiG))));

	expected_d = d[f];

	boost::successive_shortest_path_nonnegative_weights(G, s, f);
	long flow = 0;

	for (auto e: boost::make_iterator_range(boost::out_edges(s, G))) {
		flow += cap[e] - res[e];
	}

	long st = 1, dr = flow;
	long sol = 0;

	Edge e; bool succ;
	e = add_edge_(s_, s, 0, 0);

	while (st <= dr) {
		int mid = (st + dr) / 2;

		cap[e] = mid;
		if (flows(mid)) {
			sol = mid;
			st = mid + 1;
		}
		else dr = mid - 1;
	}

	std::cout << sol << '\n';
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