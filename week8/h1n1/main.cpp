#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <iostream>
#include <vector>
#include <algorithm>

#include <boost/pending/disjoint_sets.hpp>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> TDS;
typedef CGAL::Delaunay_triangulation_2<K, TDS> DT;

typedef DT::Vertex_handle Vertex_handle;
typedef DT::Face_handle Face_handle;
typedef DT::Finite_faces_iterator Finite_faces_iterator;
typedef DT::All_edges_iterator All_edges_iterator;
typedef DT::Finite_edges_iterator Finite_edges_iterator;
typedef DT::Point  P;

typedef boost::disjoint_sets_with_storage<> Disjoint_sets;

int n, m;
std::vector <P> infected;
std::vector < std::pair < K::FT, std::pair < P, K::FT> > > query;

void read() {
	infected = std::vector <P>(n);

	for (int i = 0; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		infected[i] = P(x, y);
	}

	std::cin >> m;
	query = std::vector < std::pair < K::FT, std::pair < P, K::FT> > >(m);

	for (int i = 0; i < m; i++) {
		int x, y;
		K::FT d;
		std::cin >> x >> y >> d;

		query[i].first = -d;
		query[i].second.first = P(x, y);
		query[i].second.second = i; 
	}
}


DT triang;
int faces_count;
int infinite_face;

void make_triang() {
	triang.clear();
	triang.insert(infected.begin(), infected.end());
	faces_count = 0;
	for (Finite_faces_iterator f  = triang.finite_faces_begin();
		 					   f != triang.finite_faces_end(); f++) {
		f->info() = faces_count;
		faces_count++;
	}
}

std::vector < std::pair < K::FT, std::pair <int, int> > > edges;
void find_edges() {
	edges.clear();
	infinite_face = faces_count;

	for (Finite_edges_iterator e  = triang.finite_edges_begin();
		 					   e != triang.finite_edges_end(); e++) {
		Face_handle f = e->first;
		Face_handle g = f->neighbor(e->second);
		K::FT len = triang.segment(e).squared_length();

		std::pair < K::FT, std::pair <int, int> > edge;
		edge.first = -len;

		if (!triang.is_infinite(f)) edge.second.first = f->info();
		else edge.second.first = infinite_face;

		if (!triang.is_infinite(g)) edge.second.second = g->info();
		else edge.second.second = infinite_face;
		edges.push_back(edge);

		//if (f->info() == 0 && g->info() == 1)
		//std::cout << "!" << edge.second.first << ' ' << edge.second.second << '\n';
	}

}

std::vector <char> result;

void solve() {
	make_triang();
	find_edges();
	std::sort(query.begin(), query.end());
	std::sort(edges.begin(), edges.end());

	std::vector < std::pair < K::FT, std::pair <int, int> > >::iterator edge_it;
	edge_it = edges.begin();

	result = std::vector <char>(m);

	Disjoint_sets ds(faces_count + 1);

	for (int i = 0; i < m; i++) {
		K::FT wanted_d = -query[i].first;
		K::Point_2 p = query[i].second.first;
		int index = query[i].second.second;

		Vertex_handle v = triang.nearest_vertex(p);
		K::FT d = CGAL::squared_distance(v->point(), p);

		//std::cout << d << ' ' << wanted_d << '\n';

		if (d < wanted_d) {
			result[index] = 'n';
			continue;
		}

		K::FT wanted_len = -query[i].first * 4;

		if (edge_it != edges.end()) {
			K::FT crt_len = (-1) * edge_it->first;
			while (crt_len >= wanted_len) {
				ds.union_set(edge_it->second.first, edge_it->second.second);
				edge_it++;
				if (edge_it == edges.end()) break;
				crt_len = (-1) * edge_it->first;
			}
		}

		Face_handle f = triang.locate(p);

		if (triang.is_infinite(f)) {
			result[index] = 'y';
			continue;
		}
		if (ds.find_set(infinite_face) == ds.find_set(f->info()))
			result[index] = 'y';
		else result[index] = 'n';
	}

	for (int i = 0; i < m; i++)
		std::cout << result[i];
	std::cout << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);

	while(std::cin >> n) {
		if (n == 0) break;
		read();
		//solve();
	}

	return 0;
}