#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/biconnected_components.hpp>

typedef boost::adjacency_list<
	boost::vecS, boost::vecS, boost::undirectedS,
	boost::no_property, boost::no_property> Graph;

typedef boost::graph_traits<Graph>::edge_descriptor Edge;

int n, m;
Graph G;

std::vector < std::pair <int, int> > bridges;

void read() {
	std::cin >> n >> m;

	bridges = std::vector < std::pair <int, int> >(m);

	for (int i = 0; i < m; i++) {
		std::cin >> bridges[i].first >> bridges[i].second;
		if (bridges[i].first > bridges[i].second) {
			std::swap(bridges[i].first, bridges[i].second);
		}
	}
}

inline int bridge(int x) {
	return n + x;
}

inline bool is_bridge(int x) {
	return x >= n;
}

void build_graph() {
	G = Graph(n + m);

	for (int i = 0; i < m; i++) {
		Edge e;
		bool s;

		// std::cout << bridges[i].first << ' ' << bridges[i].second << '\n';
		tie(e, s) = boost::add_edge(bridges[i].first, bridge(i), G);
		tie(e, s) = boost::add_edge(bridge(i), bridges[i].second, G);
	}
}

void solve() {
	build_graph();

	std::vector <int> b;
	articulation_points(G,
		back_inserter(b)
	);


	int cnt = 0;
	std::vector < std::pair <int, int> > output;
	for (std::vector <int>::iterator it = b.begin();
									 it != b.end(); it++) {
		if (!is_bridge(*it)) continue;
		cnt++;
		output.push_back(bridges[*it - n]);
	}

	std::cout << cnt << '\n';
	std::sort(output.begin(), output.end());

	for (std::vector < std::pair <int, int> >::iterator it = output.begin();
									 					it != output.end(); it++) {
		std::cout << it->first << ' ' << it->second << '\n';
	}
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