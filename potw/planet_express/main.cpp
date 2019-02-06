#include <iostream>
#include <vector>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list <
	boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property < boost::edge_weight_t, int > > Graph;
typedef boost::graph_traits < Graph >::edge_descriptor Edge;
typedef boost::property_map < Graph, boost::edge_weight_t >::type WeightMap;

int n, m, k, t;
Graph G;

std::vector<int> network;

WeightMap weight_map;


void read() {
	std :: cin >> n >> m >> k >> t;

	network = std::vector <int>(t);

	G = Graph(n);
	weight_map = boost::get(boost::edge_weight, G);

	for (int i = 0; i < t; i++)
		std::cin >> network[i];

	int x, y, c;
	for (int i = 0; i < m; i++) {
		std::cin >> x >> y >> c;

		Edge e; bool s;
		tie(e, s) = boost::add_edge(y, x, G);
		weight_map[e] = c;
	}
}

int comp_count = 0;

void add_edges() {
	std::vector <int> c_map(n);
	strong_components(G, &c_map[0]);

	std::map < int, std::vector <int> > comp;
	for (int i = 0; i < t; i++) {
		comp[c_map[network[i]]].push_back(network[i]);
	}

	std::map < int, std::vector <int> >::iterator it;
	comp_count = 0;
	for (it = comp.begin(); it != comp.end(); it++) {
		int v = boost::add_vertex(G);
		comp_count++;

		int c = it->second.size() - 1;

		std::vector <int> :: iterator it2;
		for (it2 = it->second.begin(); it2 != it->second.end(); it2++) {
			int u = (*it2);
			Edge e; bool s;
			tie(e, s) = boost::add_edge(u, v, G);
			weight_map[e] = c;
			tie(e, s) = boost::add_edge(v, u, G);
			weight_map[e] = 0;
		}
	}
}

void solve() {
	add_edges();

	std::vector <int> d_map(n + comp_count);

	dijkstra_shortest_paths(G, n - 1,
		distance_map(boost::make_iterator_property_map(d_map.begin(),
			boost::get(boost::vertex_index, G)))
	);

	int min_d = d_map[0];
	for (int i = 1; i < k; i++) {
		min_d = std::min(min_d, d_map[i]);
	}

	if (min_d < 1000000) std::cout << min_d << '\n';
	else std::cout << "no\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);

	int t_;
	std::cin >> t_;
	while(t_--) {
		read();
		solve();
	}
	return 0;
}