#include <iostream>
#include <vector>
#include <algorithm>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;
typedef DT::Finite_edges_iterator Finite_edges_iterator;
typedef DT::Edge_circulator Edge_circulator;

typedef K::Point_2 P;

int n;
int l, b, r, t;
std::vector < std::pair<P, int> > bacteria;
std::vector <K::FT> d;

void read() {
	std::cin >> l >> b >> r >> t;
	bacteria = std::vector < std::pair<P, int> >(n);

	for (int i = 0; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		bacteria[i] = std::make_pair(P(x, y), i);
	}
}

int time_for(K::FT d) {
	double x = sqrt(CGAL::to_double(d)) - 0.5;

	if (x <= 0) x = 0;
	else x = ceil(sqrt(x));
	return x;
}

void solve() {
	d = std::vector<K::FT>(n);
	DT triang;
	triang.insert(bacteria.begin(), bacteria.end());

	for (int i = 0; i < n; i++) {
		K::FT x = bacteria[i].first.x();
		K::FT y = bacteria[i].first.y();
		d[i] = std::min(std::min(x - l, r - x),
						std::min(y - b, t - y));
		d[i] *= d[i];
	}

	for (Finite_edges_iterator it =  triang.finite_edges_begin();
							   it != triang.finite_edges_end(); it++) {

		DT::Face_handle f = it->first;
		int i = it->second;
		
		int u = f->vertex(f->cw(i))->info();
		int v = f->vertex(f->ccw(i))->info();

		K::FT d_crt = triang.segment(it).squared_length();
		d[u] = std::min(d[u], d_crt / 4);
		d[v] = std::min(d[v], d_crt / 4);
	}

	std::sort(d.begin(), d.end());

	std::cout << time_for(d[0]) << ' ' << time_for(d[n / 2])
			  << ' ' <<  time_for(d[n - 1]) << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);

	std::cin >> n;
	for (; n != 0; std::cin >> n) {
		read();
		solve();
	}

	return 0;
}