// ALGOLAB BGL Tutorial 3
// Code snippets demonstrating 
// - MinCostMaxFlow with arbitrary edge costs using cycle_canceling
// - MinCostMaxFlow with non-negative edge costs using successive_shortest_path_nonnegative_weights

// Compile and run with one of the following:
// ++g -std=c++11 -O2 bgl_mincostmaxflow.cpp -o bgl_mincostmaxflow; ./bgl_mincostmaxflow
// g++ -std=c++11 -O2 -I path/to/boost_1_58_0 bgl_mincostmaxflow.cpp -o bgl_mincostmaxflow; ./bgl_mincostmaxflow

// Includes
// ========
// STL includes
#include <iostream>
#include <cstdlib>
// BGL includes
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/cycle_canceling.hpp>
#include <boost/graph/successive_shortest_path_nonnegative_weights.hpp>
#include <boost/graph/find_flow_cost.hpp>

// BGL Graph definitions
// ===================== 
// Graph Type with nested interior edge properties for Cost Flow Algorithms
typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> Traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, Traits::edge_descriptor,
                boost::property <boost::edge_weight_t, long> > > > > Graph; // new!
// Interior Property Maps
typedef boost::property_map<Graph, boost::edge_capacity_t>::type      EdgeCapacityMap;
typedef boost::property_map<Graph, boost::edge_weight_t >::type       EdgeWeightMap; // new!
typedef boost::property_map<Graph, boost::edge_residual_capacity_t>::type ResidualCapacityMap;
typedef boost::property_map<Graph, boost::edge_reverse_t>::type       ReverseEdgeMap;
typedef boost::graph_traits<Graph>::vertex_descriptor          Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor            Edge;
typedef boost::graph_traits<Graph>::edge_iterator  EdgeIt; // Iterator
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
        boost::property<boost::edge_weight_t, int> > DiGraph;

typedef boost::property_map<DiGraph, boost::edge_weight_t>::type DiWeightMap;
// Custom Edge Adder Class, that holds the references
// to the graph, capacity map, weight map and reverse edge map
// ===============================================================
class EdgeAdder {
    Graph &G;
    EdgeCapacityMap &capacitymap;
    EdgeWeightMap &weightmap;
    ReverseEdgeMap  &revedgemap;

public:
    EdgeAdder(Graph &G, EdgeCapacityMap &capacitymap, EdgeWeightMap &weightmap, ReverseEdgeMap &revedgemap) 
        : G(G), capacitymap(capacitymap), weightmap(weightmap), revedgemap(revedgemap) {}

    Edge addEdge(int u, int v, long c, long w) {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e; 
        revedgemap[rev_e] = e;
        return e;
    }


};

int n, m, l;
int source_;

int max_priority;


struct Agent {
    int x, y, p;
};
std::vector <Agent> agents; 

Graph G;
EdgeCapacityMap capacitymap;
EdgeWeightMap weightmap;
ReverseEdgeMap revedgemap;
ResidualCapacityMap rescapacitymap;

std::map <Edge, int> len_map;


void read() {
    std::cin >> n >> m >> l;

    agents = std::vector <Agent>(m);

    max_priority = -1;

    for (int i = 0; i < m; i++) {
        Agent a;
        std::cin >> a.x >> a.y >> a.p;
        agents[i] = a;

        max_priority = std::max(max_priority, a.p);
    }
}

void build_graph() {
    G = Graph(1 + n);
    source_ = n;

    capacitymap = boost::get(boost::edge_capacity, G);
    weightmap = boost::get(boost::edge_weight, G);
    revedgemap = boost::get(boost::edge_reverse, G);
    rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    len_map.clear();

    Edge e = eaG.addEdge(source_, 0, l, 0);
    len_map[e] = 0;

    for (int i = 0; i < m; i++) {
        Agent a = agents[i];
        int len = a.y - a.x;
        int cost = max_priority * (len) - a.p;
        Edge e = eaG.addEdge(a.x, a.y, 1, cost);
        len_map[e] = len;
    }

    for (int i = 0; i < n - 1; i++) {
        Edge e = eaG.addEdge(i, i + 1, l, max_priority);
        len_map[e] = 1;
    }
}

void solve() {
    build_graph();
    successive_shortest_path_nonnegative_weights(G, source_, n - 1);
    int cost = 0;
    EdgeIt e, eend;
    for(boost::tie(e, eend) = boost::edges(G); e != eend; ++e) {
        int flow = capacitymap[*e] - rescapacitymap[*e];
        //std::cout << flow << ' ';
        if (flow != 1) continue;
        cost += weightmap[*e] - max_priority * len_map[*e];
    }

    std::cout << (-1) * cost << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t; std::cin >> t;
    while(t--) {
        read();
        solve();
    }
    return 0;
}