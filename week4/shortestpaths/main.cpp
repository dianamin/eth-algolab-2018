#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <map>

typedef boost::adjacency_list <
			boost::vecS, boost::vecS, boost::directedS,
			boost::no_property,
			boost::property<boost::edge_weight_t, int> > Graph;
typedef boost::property_map <Graph, boost::edge_weight_t>::type WeightMap;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;


int n, m, q;
Graph G;
WeightMap weight_map;


std::map < int, std::vector < std::pair <int, int> > > query_map;

void read() {
	std::cin >> n >> m >> q;
	G = Graph(n);

	weight_map = boost::get(boost::edge_weight, G);

	for (int i = 0; i < n; i++) {
		int a, b;
		std::cin >> a >> b;
		//poz[i] = P(a, b);
	}

	for (int i = 0; i < m; i++) {
		int a, b;
		int c;
		std::cin >> a >> b >> c;

		Edge e;
		bool s;

		tie(e, s) = boost::add_edge(a, b, G);
		weight_map[e] = c;
	}

	query_map.clear();
	for (int i = 0; i < q; i++) {
		int s, t;
		std::cin >> s >> t;
		query_map[s].push_back(std::make_pair(t, i));
	}
}

void solve() {
	std::map < int, std::vector < std::pair <int, int> > >::iterator it;

	std::vector < int > result(q);

	for (it = query_map.begin(); it != query_map.end(); it++) {
		int s = it->first;
		

		std::vector < int > d_map(n);

		dijkstra_shortest_paths(G, s,
			distance_map(boost::make_iterator_property_map(
				d_map.begin(),
				boost::get(boost::vertex_index, G)))
		);

		std::vector < std::pair <int, int> > ::iterator it2;
		for (it2 = (it->second).begin(); it2 != (it->second).end(); it2++) {
			result[it2->second] = d_map[it2->first];
		}
	}

	for (int i = 0; i < q; i++) {
		if (result[i] == INT_MAX) std::cout << "unreachable\n";
		else std::cout << result[i] << '\n';
	}
}


int main() {
	std::ios_base::sync_with_stdio(false);
	
	read();
	solve();
	return 0;
}