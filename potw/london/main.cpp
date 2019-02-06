#include <iostream>
#include <vector>
#include <string>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

typedef boost::adjacency_list_traits <boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list <boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property <boost::edge_capacity_t, long,
	boost::property <boost::edge_residual_capacity_t, long,
	boost::property <boost::edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef boost::property_map <Graph, boost::edge_capacity_t>::type Capacity;
typedef boost::property_map <Graph, boost::edge_residual_capacity_t>::type ResCapacity;
typedef boost::property_map <Graph, boost::edge_reverse_t>::type RevEdge;

typedef boost::graph_traits <Graph>::edge_descriptor Edge;



const int PAIRS = 26 * 26;
const int LETTERS = 26;

int n, h, w;

int letters_occ[LETTERS];
int pairs_occ[LETTERS][LETTERS];


Graph G;
int s, t;
Capacity capacity_map_;
ResCapacity res_capacity_map_;
RevEdge rev_edge_map_;


void add_edge_(int from, int to, long capacity) {
	Edge e, rev_e; bool success;

	boost::tie(e, success) = boost::add_edge(from, to, G);
	boost::tie(rev_e, success) = boost::add_edge(to, from, G);
	capacity_map_[e] = capacity;
	capacity_map_[rev_e] = 0; // reverse edge has no capacity!
	rev_edge_map_[e] = rev_e;
	rev_edge_map_[rev_e] = e;
}

inline int index(char C) {
	return C - 'A';
}

void read() {
	for (int i = 0; i < LETTERS; i++)
		letters_occ[i] = 0;

	for (int i = 0; i < LETTERS; i++)
		for (int j = 0; j < LETTERS; j++)
			pairs_occ[i][j] = 0;

	std::cin >> h >> w;

	std::string message;
	std::cin >> message;

	n = message.length();

	for (int i = 0; i < n; i++) {
		letters_occ[index(message[i])]++;
	}


	std::vector < std::vector <char> > f(h, std::vector <char>(w));


	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++) {
			std::cin >> f[i][j];
		}

	for (int i = 0; i < h; i++)
		for (int k = 0, j = w - 1; k < w; k++, j--) {
			char a, b;
			a = f[i][j];
			std::cin >> b;
			if (a > b) std::swap(a, b);
			//std::cout << a << ' ' << b << ''
			pairs_occ[index(a)][index(b)]++;
		}
}

inline int letter_index(int i) {
	return 1 + PAIRS + i;
}

void build_graph() {
	G = Graph(1 + PAIRS + LETTERS + 1);
	s = 0;
	t = 1 + PAIRS + LETTERS;

	capacity_map_ = boost::get(boost::edge_capacity, G);
	res_capacity_map_ = boost::get(boost::edge_residual_capacity, G);
	rev_edge_map_ = boost::get(boost::edge_reverse, G);

	int node_index = 1;
	for (int i = 0; i < LETTERS; i++)
		for (int j = 0; j < LETTERS; j++) {
			add_edge_(s, node_index, pairs_occ[i][j]);
			add_edge_(node_index, letter_index(i), pairs_occ[i][j]);
			add_edge_(node_index, letter_index(j), pairs_occ[i][j]);
			node_index++;
		}

	for (int i = 0; i < LETTERS; i++) {
		add_edge_(letter_index(i), t, letters_occ[i]);
	}
}

void solve() {
	build_graph();
	int flow = boost::push_relabel_max_flow(G, s, t);
	int expected = 0;
	for (int i = 0; i < LETTERS; i++)
		expected += letters_occ[i];

	//std::cout << flow << ' ' << expected << ' ';
	if (expected == flow) std::cout << "Yes\n";
	else std::cout << "No\n";
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