#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/range/algorithm/set_algorithm.hpp>

typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::undirectedS,
	boost::no_property, boost::no_property> Graph;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;

int n, c, f;
Graph G;

std::vector < std::vector <std::string> > characteristics;

void read() {
	std::cin >> n >> c >> f;

	characteristics = std::vector < std::vector <std::string> >(n,
							std::vector <std::string>(c));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < c; j++)
			std::cin >> characteristics[i][j];
		std::sort(characteristics[i].begin(), characteristics[i].end());
	}
}

int common_characteristics(int a, int b) {
	std::vector <std::string> intersection;

	boost::range::set_intersection(characteristics[a], characteristics[b],
								   std::back_inserter(intersection));

	return intersection.size();
}

void build_graph() {
	G = Graph(n);

	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			int c = common_characteristics(i, j);
			if (c <= f) continue;

			Edge e; bool s;
			tie(e, s) = boost::add_edge(i, j, G);
		}
}

void solve() {
	build_graph();

	std::vector <int> mate(n);

	edmonds_maximum_cardinality_matching(G, &mate[0]);

	for (int i = 0; i < n; i++) {
		if (mate[i] == -1) {
			std::cout << "optimal\n";
			return;
		}
	}

	std::cout << "not optimal\n";
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