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
#include <set>
#include <map>
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
typedef boost::graph_traits<Graph>::out_edge_iterator  OutEdgeIt; // Iterator


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

    void addEdge(int u, int v, long c, long w) {
        Edge e, rev_e;
        boost::tie(e, boost::tuples::ignore) = boost::add_edge(u, v, G);
        boost::tie(rev_e, boost::tuples::ignore) = boost::add_edge(v, u, G);
        capacitymap[e] = c;
        weightmap[e] = w; // new!
        capacitymap[rev_e] = 0;
        weightmap[rev_e] = -w; // new
        revedgemap[e] = rev_e; 
        revedgemap[rev_e] = e; 
    }
};


struct Booking {
    int s, t, d, a, p;

    Booking() {}

    Booking(int s_, int t_, int d_, int a_, int p_) {
        s = s_;
        t = t_;
        d = d_;
        a = a_;
        p = p_;
    }
};



const int MAXL = 100;
const int MAXT = 100000;
const int MAXP = 100;

int INF;

int source_;
int target_;


int N, S;
std::vector <int> l;
std::vector <Booking> booking;

Graph G;
EdgeCapacityMap capacitymap;
EdgeWeightMap weightmap;
ReverseEdgeMap revedgemap;
ResidualCapacityMap rescapacitymap;


void read() {
    std::cin >> N >> S;

    INF = MAXL*S;

    l = std::vector <int>(S);
    booking = std::vector <Booking>(N);

    for (int i = 0; i < S; i++)
        std::cin >> l[i];

    for (int i = 0; i < N; i++) {
        int s, t, d, a, p;
        std::cin >> s >> t >> d >> a >> p;
        s--; t--;
        booking[i] = Booking(s, t, d, a, p);
    }
}

void build_graph() {
    std::vector< std::set<int> > times(S);
    for (int i = 0; i < S; i++) {
        times[i].insert(0);
        times[i].insert(MAXT);
    }

    for (int i = 0; i < N; i++) {
        times[booking[i].s].insert(booking[i].d);
        times[booking[i].t].insert(booking[i].a);
    }

    std::vector< std::map<int, int> > m(S);
    std::vector<int> sum(S + 1);
    sum[0] = 0;
    for (int i = 0; i < S; i++) {
        int cnt = 0;
        for (std::set <int> :: iterator t = times[i].begin();
                                   t != times[i].end(); t++) {
            m[i][*t] = cnt++;
        }
        sum[i + 1] = sum[i] + m[i].size();
    }

    int T = sum.back();
    G = Graph(1 + T + 1);
    source_ = T;
    target_ = T + 1;
    capacitymap = boost::get(boost::edge_capacity, G);
    weightmap = boost::get(boost::edge_weight, G);
    revedgemap = boost::get(boost::edge_reverse, G);
    rescapacitymap = boost::get(boost::edge_residual_capacity, G);
    EdgeAdder eaG(G, capacitymap, weightmap, revedgemap);

    for (int i = 0; i < S; i++) {
        eaG.addEdge(source_, sum[i], l[i], 0);
        eaG.addEdge(sum[i + 1] - 1, target_, INF, 0);

        int it = -1; int lastt = 0;
        for (std::set <int> :: iterator t = times[i].begin();
                                   t != times[i].end(); t++) {
            if (it != -1) 
                eaG.addEdge(sum[i] + it, sum[i] + it + 1, INF, MAXP * (*t - lastt));
            it++;
            lastt = *t;
        }
    }

    for (int i = 0; i < N; i++) {
        Booking b = booking[i];
        int from = sum[b.s] + m[b.s][b.d];
        int to = sum[b.t] + m[b.t][b.a];
        int cost = (b.a - b.d) * MAXP - b.p;
        eaG.addEdge(from, to, 1, cost);
    }
}

void solve() {
    build_graph();

    successive_shortest_path_nonnegative_weights(G, source_, target_);
    int flow = 0;
    OutEdgeIt e, eend;
    for(boost::tie(e, eend) = boost::out_edges(boost::vertex(source_,G), G); e != eend; ++e) {
        // std::cout << *e << '\n';
        flow += capacitymap[*e] - rescapacitymap[*e];
    }
    // boost::cycle_canceling(G);
    int cost = flow * MAXP * MAXT - boost::find_flow_cost(G);

    std::cout << cost << '\n';
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