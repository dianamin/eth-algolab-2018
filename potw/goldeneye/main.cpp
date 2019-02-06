#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

#include <boost/pending/disjoint_sets.hpp>

#include <algorithm>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef K::Point_2 P;

typedef boost::disjoint_sets_with_storage<> DS;

int n, m;
K::FT p;

std::vector < std::pair <P, int> > jammers;
std::vector < std::pair <P, P> > missions;

void read() {
  std::cin >> n >> m >> p;
  jammers = std::vector < std::pair <P, int> >(n);
  missions = std::vector < std::pair <P, P> >(m);

  for (int i = 0; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    jammers[i] = std::make_pair(P(x, y), i);
  }

  for (int i = 0; i < m; i++) {
    int x1, y1, x2, y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    missions[i] = std::make_pair(P(x1, y1), P(x2, y2));
  }
}


std::vector < std::pair < K::FT, std::pair <int, int> > > edges;

void solve() {
  DT triang;
  triang.insert(jammers.begin(), jammers.end());
  edges.clear();
  for (DT::Finite_edges_iterator e  = triang.finite_edges_begin();
                                 e != triang.finite_edges_end(); e++) {
    DT::Face_handle f = e->first;
    DT::Vertex_handle u = f->vertex((e->second + 1) % 3);
    DT::Vertex_handle v = f->vertex((e->second + 2) % 3);
    K::FT l = CGAL::squared_distance(u->point(), v->point());
    edges.push_back(std::make_pair(l, std::make_pair(u->info(), v->info())));
  }

  std::sort(edges.begin(), edges.end());
  std::vector < std::pair < K::FT, std::pair <int, int> > >::iterator it_p;

  K::FT a = 0;
  K::FT b = 0;
  std::vector < std::pair < K::FT, std::pair <int, int> > >::iterator it_a;
  std::vector < std::pair < K::FT, std::pair <int, int> > >::iterator it_b;

  DS ds(n);
  for (it_p = edges.begin(); it_p != edges.end(); it_p++) {
    if (it_p->first > p) break;
    ds.union_set(it_p->second.first, it_p->second.second);
  }

  DS ds_a(n);
  DS ds_b(n);
  it_a = edges.begin();
  it_b = edges.begin();

  for (int i = 0; i < m; i++) {
    P s = missions[i].first;
    P t = missions[i].second;

    DT::Vertex_handle v_s = triang.nearest_vertex(s);
    DT::Vertex_handle v_t = triang.nearest_vertex(t);

    K::FT needed = std::max(4 * CGAL::squared_distance(v_s->point(), s),
                            4 * CGAL::squared_distance(v_t->point(), t));
    bool result;
    if (needed > p) result = false;
    else {
      if (ds.find_set(v_s->info()) == ds.find_set(v_t->info())) {
        result = true;
      }
      else {
        result = false;
      }
    } 

    if (result) {
      //std::cout << "\nyey\n";
      while (it_b != edges.end() &&
             ds_b.find_set(v_s->info()) != ds_b.find_set(v_t->info())) {
        //std::cout << "b: " << it_b->first << '\n';
        ds_b.union_set(it_b->second.first, it_b->second.second);
        b = std::max(it_b->first, b);
        it_b++;
      }
      b = std::max(b, needed);
    }

   // std::cout << a << ' ' << needed << '\n';
    while (it_a != edges.end() &&
           ds_a.find_set(v_s->info()) != ds_a.find_set(v_t->info())) {
      ds_a.union_set(it_a->second.first, it_a->second.second);
      //std::cout << it_a->first;
      a = std::max(it_a->first, a);
      //std::cout <<a << ' ';
      it_a++;
      if (it_a == edges.end()) break;
    }
    a = std::max(a, needed);
  
    if (result) std::cout << 'y';
    else std::cout << 'n';
  }
  std::cout << '\n';
  std::cout << std::fixed << std::setprecision(0) << a << '\n' << b << '\n';
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
