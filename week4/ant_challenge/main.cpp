#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

typedef boost::adjacency_list <
			boost::vecS, boost::vecS, boost::undirectedS,
			boost::no_property,
			boost::property <boost::edge_index_t, int>
		> Graph;


typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

int n, e, s, a, b;
Graph G;

std::vector < std::vector <int> > weights;
std::vector <int> hive;

boost::property_map<Graph, boost::edge_index_t>::type indices; 

void read() {
	std::cin >> n >> e >> s >> a >> b;
	//std::cout << 

	G = Graph(n);

	indices = boost::get(boost::edge_index, G);


	weights = std::vector < std::vector <int> >(s, std::vector <int>(e));
	hive = std::vector <int>(s);


	for (int i = 0; i < e; i++) {
		int x, y;
		std::cin >> x >> y;
		//std::cout << x << ' ' << y << '\n';

		Edge edge; bool suc;
		tie(edge, suc) = boost::add_edge(x, y, G);
		indices[edge] = i;
		//std::cout << indices[edge] << '\n';

		for (int j = 0; j < s; j++)
			std::cin >> weights[j][i];
	}

	for (int i = 0; i < s; i++)
		std::cin >> hive[i];
}

void solve() {
	std::vector <int> final_weight(e, INT_MAX);
	for (int i = 0; i < s; i++) {

		std::vector <int> pred_map(n);

		prim_minimum_spanning_tree(G,
			boost::make_iterator_property_map(pred_map.begin(),
											  boost::get(boost::vertex_index, G)),
			boost::root_vertex(hive[i]).
			weight_map(boost::make_iterator_property_map(
							  weights[i].begin(),
							  indices))
		);

		for (int node = 0; node < n; node++) {
			int pred = pred_map[node];
			if (pred == node) continue;
			Edge e; bool s;
			tie(e, s) = boost::edge(pred, node, G);
			int index = indices[e];
			final_weight[index] = std::min(final_weight[index],
										   weights[i][index]);
		}
	}

	std::vector <int> d_map(n);
	boost::dijkstra_shortest_paths(G, a,
		distance_map(boost::make_iterator_property_map(
				d_map.begin(), boost::get(boost::vertex_index, G)
			)).
		weight_map(boost::make_iterator_property_map(
				final_weight.begin(),
				indices
			))
	);


	std::cout << d_map[b] << '\n';
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