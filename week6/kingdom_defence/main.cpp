#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property<boost::edge_capacity_t, long,
	boost::property<boost::edge_residual_capacity_t, long,
	boost::property<boost::edge_reverse_t, Traits::edge_descriptor> > > > Graph;
typedef boost::property_map<Graph, boost::edge_capacity_t>::type EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type ReverseEdgeMap;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;

Graph G;
EdgeCapacityMap capacity_map_;
ResidualCapacityMap res_capacity_map_;
ReverseEdgeMap rev_map;

void add_edge_(int from, int to, long capacity) {
	bool s;
	Edge e;

	boost::tie(e, s) = boost::add_edge(from, to, G);

	Edge rev_e;
	boost::tie(rev_e, s) = boost::add_edge(to, from, G);
	rev_map[e] = rev_e;
	rev_map[rev_e] = e;
	capacity_map_[rev_e] = 0;
	capacity_map_[e] = capacity;
}

int n, m;

std::vector <int> need;

int s, t;

void read() {
	std::cin >> n >> m;

	G = Graph(1 + n + 1);
	capacity_map_ = boost::get(boost::edge_capacity, G);
	res_capacity_map_ = boost::get(boost::edge_residual_capacity, G);
	rev_map = boost::get(boost::edge_reverse, G);

	s = n;
	t = n + 1;

	need = std::vector <int>(n);

	for (int i = 0; i < n; i++) {
		int g, d;
		std::cin >> g >> d;
		need[i] = d - g;
	}

	for (int i = 0; i < m; i++) {
		int from, to, c, C;
		std::cin >> from >> to >> c >> C;
		need[from] += c;
		need[to] -= c;
		add_edge_(from, to, C - c);
	}
}

void solve() {
	int expected = 0;
	for (int i = 0; i < n; i++) {
		if (need[i] > 0) {
			expected += need[i];
			add_edge_(i, t, need[i]);
		}
		if (need[i] < 0) {
			add_edge_(s, i, (-1) * need[i]);
		}
	}

	int flow = boost::push_relabel_max_flow(G, s, t);
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