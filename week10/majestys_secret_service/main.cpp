#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list<vecS, vecS, undirectedS, no_property> Graph;
typedef adjacency_list<vecS, vecS, directedS, no_property,
		property<edge_weight_t, int> > DiGraph;
typedef property_map<DiGraph, edge_weight_t>::type WeightMap;
typedef graph_traits<DiGraph>::vertex_descriptor Vertex;
typedef graph_traits<DiGraph>::edge_descriptor Edge;

int n, m, a, s, c, d;

DiGraph G;
WeightMap weight_map_;
vector < vector <int> > dist_map;
vector < vector <int> > shelter_dist;

void read() {
	G.clear();
	dist_map.clear();
	shelter_dist.clear();
	// weight_map_.clear();

	cin >> n >> m >> a >> s >> c >> d;
	G = DiGraph(n);
	weight_map_ = get(edge_weight, G);

	for (int i = 0; i < m; i++) {
		char w;
		int x, y, z;
		cin >> w >> x >> y >> z;

		Edge e;
		tie (e, tuples::ignore) = add_edge(x, y, G);
		weight_map_[e] = z;

		if (w == 'L') {
			tie(e, tuples::ignore) = add_edge(y, x, G);
			weight_map_[e] = z;
		}
	}

	dist_map = vector < vector <int> >(a, vector <int>(n));

	for (int i = 0; i < a; i++) {
		int node;
		cin >> node;
		dijkstra_shortest_paths(G, node,
			distance_map(make_iterator_property_map(dist_map[i].begin(),
													get(vertex_index, G))));
	}

	shelter_dist = vector < vector <int> >(a, vector <int>(s));
	for (int i = 0; i < s; i++) {
		int node;
		cin >> node;

		for (int j = 0; j < a; j++)
			shelter_dist[j][i] = dist_map[j][node];
	}
}

void solve() {
	int low = 0, high = INT_MAX;

	while (low < high) {
		int mid = low + (high - low) / 2;

		Graph GG(a + c * s);

		for (int agent = 0; agent < a; agent++) {
			for (int shelter = 0; shelter < s; shelter++) {
				if (shelter_dist[agent][shelter] == INT_MAX) continue;
				for (int cap = 0; cap < c; cap++) {
					if (shelter_dist[agent][shelter] + (cap + 1) * d <= mid) {
						add_edge(agent, a + cap * s + shelter, GG);
					}
				}
			}
		}

		// max matching
		vector <Vertex> mate_map(a + c * s);
		edmonds_maximum_cardinality_matching(GG,
			make_iterator_property_map(mate_map.begin(),
									   get(vertex_index, GG)));

		const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();
		int matching_size = 0;
		for (int agent = 0; agent < a; agent++) {
			matching_size += (mate_map[agent] != NULL_VERTEX);
		}
		if (matching_size == a) high = mid;
		else low = mid + 1;
	}

	cout << low << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);

	int t; cin >> t;
	while(t--) {
		read();
		solve();
	}
}