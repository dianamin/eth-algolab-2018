#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

#include <boost/pending/disjoint_sets.hpp>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;

typedef boost::disjoint_sets_with_storage<> DS;

typedef  CGAL::Min_circle_2_traits_2<K>  Traits;
typedef  CGAL::Min_circle_2<Traits>      Min_circle;

typedef K::Point_2 P;

int n, m;
K::FT r;

std::vector <P> tree;
std::vector < std::pair <K::FT, std::pair <P, int> > > balloon;
std::vector <char> output;

void read() {
  std::cin >> n >> m >> r;
  tree = std::vector <P>(n);
  balloon = std::vector < std::pair <K::FT, std::pair <P, int> > >(m);

  for (int i = 0; i < n; i++) {
    long long x, y;
    std::cin >> x >> y;
    tree[i] = P(x, y);
  }

  for (int i = 0; i < m; i++) {
    long long x, y, s;
    std::cin >> x >> y >> s;
    balloon[i].first = -s;
    balloon[i].second.first = P(x, y);
    balloon[i].second.second = i;
  }
}

DT triang;
int inf_face;
std::vector < std::pair <K::FT, int> > min_d;

void make_triang() {
  triang.clear();
  triang.insert(tree.begin(), tree.end());
  int faces_count = 0;
  for (DT::Finite_faces_iterator f  = triang.finite_faces_begin();
                                 f != triang.finite_faces_end(); f++) {
    f->info() = faces_count;
    faces_count++;
  }


  min_d = std::vector < std::pair <K::FT, int> >(faces_count);
  for (DT::Finite_faces_iterator f  = triang.finite_faces_begin();
                                 f != triang.finite_faces_end(); f++) {
    std::vector < P > points(3);

    for (int i = 0; i < 3; i++)
      points[i] = f->vertex(i)->point();

    Min_circle mc(points.begin(), points.end());
    min_d[f->info()] = std::make_pair(-mc.circle().squared_radius(), f->info());
  }

  inf_face = faces_count;
}

std::vector < std::pair < K::FT, std::pair <int, int> > > edges;

void find_edges() {
  edges.clear();

  for (DT::Finite_edges_iterator e  = triang.finite_edges_begin();
                                 e != triang.finite_edges_end(); e++) {
    DT::Face_handle f = e->first;
    DT::Face_handle g = f->neighbor(e->second);

    std::pair < K::FT, std::pair <int, int> > edge;

    edge.first = -triang.segment(e).squared_length();

    if (triang.is_infinite(f)) edge.second.first = inf_face;
    else edge.second.first = f->info();

    if (triang.is_infinite(g)) edge.second.second = inf_face;
    else edge.second.second = g->info();

    edges.push_back(edge);
  }
}

void solve() {
  make_triang();
  find_edges();

  std::sort(balloon.begin(), balloon.end());
  std::sort(edges.begin(), edges.end());
  std::sort(min_d.begin(), min_d.end());

  output = std::vector <char>(m);

  std::vector < std::pair < K::FT, std::pair <int, int> > >::iterator to_pass;
  std::vector < std::pair <K::FT, int> >::iterator to_fly;

  to_pass = edges.begin();
  to_fly = min_d.begin();

  DS ds(inf_face + 1);
  

  for (int i = 0; i < m; i++) {
    K::FT s = (-1) * balloon[i].first;
    P p = balloon[i].second.first;
    int index = balloon[i].second.second;

    K::FT wanted_len = 4 * (r + s) * (r + s);
    K::FT fly_len = 4 * (r + s) * (r + s);


    DT::Vertex_handle v = triang.nearest_vertex(p);
    if (CGAL::squared_distance(v->point(), p) < (r + s) * (r + s)) {
      output[index] = 'n';
      continue;
    }

    if (to_pass != edges.end()) {
      K::FT crt_len = (-1) * to_pass->first;
      while (crt_len >= wanted_len) {
        ds.union_set(to_pass->second.first, to_pass->second.second);
        to_pass++;
        if (to_pass == edges.end()) break;
        crt_len = (-1) * to_pass->first;
      }
    }


    if (to_fly != min_d.end()) {
      K::FT crt_d = (-1) * to_fly->first;
      while(crt_d >= fly_len) {
        ds.union_set(to_fly->second, inf_face);
        to_fly++;
        if (to_fly == min_d.end()) break;
        crt_d = (-1) * to_fly->first;
      }
    }

    DT::Face_handle f = triang.locate(p);

    if (triang.is_infinite(f) ||
        ds.find_set(f->info()) == ds.find_set(inf_face)) 
      output[index] = 'y';
    else output[index] = 'n';
  }

  for (int i = 0; i < m; i++) {
    std::cout << output[i];
  }
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