#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

using namespace std;
using namespace boost;

// Directed graph with integer weights on edges.
typedef adjacency_list<vecS, vecS, directedS, no_property, property<edge_weight_t, int> > Graph;
typedef graph_traits<Graph>::vertex_descriptor		Vertex;	// Vertex type		
typedef graph_traits<Graph>::edge_descriptor		Edge;	// Edge type
typedef graph_traits<Graph>::edge_iterator		EdgeIt;	// Edge iterator
// Property map edge -> weight
typedef property_map<Graph, edge_weight_t>::type	WeightMap;

int k;
int n;
Graph g_;
WeightMap weightmap_;

vector < vector <int> > v;

inline int index(int i, int j) {
	if (i == 0) return j;
	return i * (i + 1) / 2 + j;
}

void read() {
	cin >> k;
	n = (k * (k + 1) / 2);
	g_ = Graph(n);
	weightmap_ = get(edge_weight, g_);
	Edge e;	bool success;

	v = vector < vector <int> >(k);

	for (int i = 0; i < k; i++) {
		v[i] = vector <int>(i + 1);
		for (int j = 0; j <= i; j++) {
			cin >> v[i][j];

			int ind = index(i, j);

			if (i != k - 1) { // avem unde merge în jos
				Edge e1;
				tie(e1, success) = add_edge(ind, index(i + 1, j), g_);
				weightmap_[e1] = v[i][j];
				//cout << i << ' ' << j << ": " << i + 1 << ' ' << j << weightmap_[e] << ' ';
				
				Edge e2;
				tie(e2, success) = add_edge(ind, index(i + 1, j + 1), g_);
				weightmap_[e2] = v[i][j];
				//cout << i << ' ' << j << ": " << i + 1 << ' ' << j + 1 << weightmap_[e] << '\n';
			}

			if (j != i) { // am unde merge din stanga
				if (i != 0) {
					tie(e, success) = add_edge(ind, index(i - 1, j), g_);
					weightmap_[e] = v[i][j];
				}

				tie(e, success) = add_edge(ind, index(i, j + 1), g_);
				weightmap_[e] = v[i][j];
			}

			if (j != 0) {
				if (i != 0) {
					tie(e, success) = add_edge(ind, index(i - 1, j - 1), g_);
					weightmap_[e] = v[i][j];
				}

				tie(e, success) = add_edge(ind, index(i, j - 1), g_);
				weightmap_[e] = v[i][j];
			}
		}
	}
}

void solve() {
	vector<Vertex> predmap;
	predmap = vector<Vertex>(n);
	vector<int> d_top(n);
	dijkstra_shortest_paths(g_, index(0, 0),
			predecessor_map(make_iterator_property_map(
					predmap.begin(), get(vertex_index, g_))).
			distance_map(make_iterator_property_map(
					d_top.begin(), get(vertex_index, g_))));


	predmap = vector<Vertex>(n);
	vector<int> d_left(n);
	dijkstra_shortest_paths(g_, index(k - 1, 0),
			predecessor_map(make_iterator_property_map(
					predmap.begin(), get(vertex_index, g_))).
			distance_map(make_iterator_property_map(
					d_left.begin(), get(vertex_index, g_))));


	predmap = vector<Vertex>(n);
	vector<int> d_right(n);
	dijkstra_shortest_paths(g_, index(k - 1, k - 1),
			predecessor_map(make_iterator_property_map(
					predmap.begin(), get(vertex_index, g_))).
			distance_map(make_iterator_property_map(
					d_right.begin(), get(vertex_index, g_))));

	
	int min_burden = INT_MAX;

	for (int i = 0; i < k; i++)
		for (int j = 0; j <= i; j++) {
			int ind = index(i, j);
			min_burden = min(
				min_burden,
				d_top[ind] + d_left[ind] + d_right[ind] + v[i][j]
			);
		}

	cout << min_burden << '\n';
}


int main() {
	ios_base::sync_with_stdio(false);
	int t;
	cin >> t;
	while(t--) {
		read();
		solve();
	}
	return 0;
}