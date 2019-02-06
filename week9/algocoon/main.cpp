#include <iostream>
#include <vector>
#include <queue>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>


typedef boost::adjacency_list_traits<
	boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list <
	boost::vecS, boost::vecS, boost::directedS,
	boost::no_property,
	boost::property <boost::edge_capacity_t, long,
	boost::property <boost::edge_residual_capacity_t, long,
	boost::property <boost::edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef boost::graph_traits <Graph>::edge_descriptor Edge;

typedef boost::property_map <Graph, boost::edge_capacity_t>::type CapacityMap;
typedef boost::property_map <Graph, boost::edge_residual_capacity_t>::type ResCapacityMap;
typedef boost::property_map <Graph, boost::edge_reverse_t>::type RevEdgeMap;

Graph G;
CapacityMap cap;
ResCapacityMap res;
RevEdgeMap rev;

void add_edge_(int a, int b, long c) {
	Edge e;
	Edge rev_e;
	bool s;
	boost::tie(e, s) = boost::add_edge(a, b, G);
	boost::tie(rev_e, s) = boost::add_edge(b, a, G);

	cap[e] = c;
	cap[rev_e] = 0;
	rev[e] = rev_e;
	rev[rev_e] = e;
}

int n, m;

void read() {
	std::cin >> n >> m;

	G = Graph(n);
	cap = boost::get(boost::edge_capacity, G);
	res = boost::get(boost::edge_residual_capacity, G);
	rev = boost::get(boost::edge_reverse, G);

	for (int i = 0; i < m; i++) {
		int a, b, c;
		std::cin >> a >> b >> c;
		add_edge_(a, b, c);
	}
}

std::vector <int> viz;

void visit(int s) {
	std::queue <int> Q;
	Q.push(s);
	viz = std::vector <int>(n, false);
	
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		if (viz[v]) continue;
		viz[v] = true;
		for (auto e: boost::make_iterator_range(boost::out_edges(v, G))) {
			if (res[e] == 0) continue;
			int u = boost::target(e, G);
			if (!viz[u]) Q.push(u);
		}
	}
} 

void solve() {
	int s_, t_, cost_ = INT_MAX;
	for (int s = 0; s < n; s++) {
		long cost = boost::push_relabel_max_flow(G, s, (s + 1) % n); 
		if (cost < cost_) {
			cost_ = cost;
			s_ = s;
			t_ = (s + 1) % n;
		}
	}

	boost::push_relabel_max_flow(G, s_, t_); 
	visit(s_);

	std::cout << cost_ << '\n';
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if (viz[i]) cnt++;
	std::cout << cnt << ' ';
	for (int i = 0; i < n; i++)
		if (viz[i]) std::cout << i << ' ';
	std::cout << '\n';
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