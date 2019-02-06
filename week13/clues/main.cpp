#include <iostream>
#include <vector>
#include <stack>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<std::pair<int, int>, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> DT;

typedef K::Point_2 P;

using namespace std;

int n, m;
K::FT r;
std::vector <P> stations;

std::vector < vector <int> > graph;

void read() {
	std::cin >> n >> m >> r;
	r *= r;
	stations = std::vector <P>(n);

	for (int i = 0; i < n; i++) {
		K::FT x, y;
		std::cin >> x >> y;
		stations[i] = P(x, y);
	}
}

DT triang;

std::vector<P> col1;
std::vector<P> col0;

bool try_coloring() {
	triang.clear();
	triang.insert(stations.begin(), stations.end());

	DT::Finite_vertices_iterator v;
	int comp = 0;

	col0.clear();
	col1.clear();

	DT triang0, triang1;

	for (v  = triang.finite_vertices_begin();
		 v != triang.finite_vertices_end(); v++) {
		int comp_v = v->info().first;
		if (comp_v) continue;
		comp++;
		v->info().first = comp;
		v->info().second = 0; //color
		std::stack < DT::Vertex_handle > st;
		st.push(v);

		triang0.insert(v->point());

		while (!st.empty()) {
			DT::Vertex_handle v = st.top();
			st.pop();
			DT::Vertex_circulator c = triang.incident_vertices(v);
			
			do {
				if (triang.is_infinite(c)) continue;
				if (CGAL::squared_distance(v->point(), c->point()) > r)
					continue;

				if (v->info().first == c->info().first) {
					if (v->info().second == c->info().second) return false;
					continue;
				}
				c->info().first = v->info().first;
				c->info().second = 1 - v->info().second;
				st.push(c);

				if (c->info().second == 0) col0.push_back(c->point());
				else col1.push_back(c->point());
			} while (++c != triang.incident_vertices(v));
		}
	}

	triang0.insert(col0.begin(), col0.end());
	triang1.insert(col1.begin(), col1.end());

	for (DT::Finite_edges_iterator e = triang0.finite_edges_begin();
								   e != triang0.finite_edges_end(); e++) {
		if (triang0.segment(*e).squared_length() < r) return false;
	}
	for (DT::Finite_edges_iterator e = triang1.finite_edges_begin();
								   e != triang1.finite_edges_end(); e++) {
		if (triang1.segment(*e).squared_length() < r) return false;
	}


	return true;
}

void solve() {
	bool can_try = try_coloring();
	if (!can_try) {
		for (int i = 0; i < m; i++) {
			K::FT x1, y1, x2, y2;
			std::cin >> x1 >> y1 >> x2 >> y2;
			std::cout << 'n';
		}
		std::cout << '\n';
		return;
	}

	for (int i = 0; i < m; i++) {
		K::FT x1, y1, x2, y2;
		std::cin >> x1 >> y1 >> x2 >> y2;
		P a(x1, y1);
		P b(x2, y2);
		//std::cout << CGAL::squared_distance(a, b) << ' '<< r << '\n';
		if (CGAL::squared_distance(a, b) <= r) {
			std::cout << 'y';
			continue;
		}

		DT::Vertex_handle p_v = triang.nearest_vertex(a);
		if (CGAL::squared_distance(p_v->point(), a) > r) {
			std::cout << 'n';
			continue;
		}

		DT::Vertex_handle p_u = triang.nearest_vertex(b);
		if (CGAL::squared_distance(p_u->point(), b) > r) {
			std::cout << 'n';
			continue;
		}

		int v = p_v->info().first;
		int u = p_u->info().first;


		if (u == v)
			std::cout << "y";
		else std::cout << "n";
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
	return 0;
}