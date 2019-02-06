#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list <
			boost::vecS, boost::vecS, boost::undirectedS,
			boost::no_property,
			boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::property_map <Graph, boost::edge_weight_t>::type WeightMap;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;

int n, m;
Graph G;
WeightMap weight_map;

void read() {
	std::cin >> n >> m;
	G = Graph(n);

	weight_map = boost::get(boost::edge_weight, G);

	for (int i = 0; i < m; i++) {
		int a, b, c;
		std::cin >> a >> b >> c;

		Edge e;
		bool s;

		tie(e, s) = boost::add_edge(a, b, G);
		weight_map[e] = c;
	}
}

void solve() {
	std::vector < Edge > spanning_tree;
	kruskal_minimum_spanning_tree(G, back_inserter(spanning_tree));

	int total = 0;
	for (std::vector < Edge >::iterator e = spanning_tree.begin();
										e != spanning_tree.end(); e++)
		total += weight_map[*e];

	std::cout << total << ' ';

	std::vector < int > d_map(n);

	dijkstra_shortest_paths(G, 0,
			distance_map(boost::make_iterator_property_map(
				d_map.begin(),
				boost::get(boost::vertex_index, G)))
		);

	int max_d = 0;
	for (int i = 0; i < d_map.size(); i++) {
		// std::cout << d_map[i] << ' ';
		if (d_map[i] == INT_MAX) continue;
		max_d = std::max(max_d, d_map[i]);
	}

	std::cout << max_d << '\n';
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