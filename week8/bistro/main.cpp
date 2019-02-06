#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef DT::Vertex_handle Vertex_handle;
typedef K::Point_2 P;

int n, m;

std::vector <P> existing;
std::vector <P> possible;

void read() {
	existing = std::vector<P>(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		existing[i] = P(x, y);
	}

	std::cin >> m;
	possible = std::vector<P>(m);
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		possible[i] = P(x, y);
	}
}

void solve() {
	DT triang;
	triang.insert(existing.begin(), existing.end());

	for (int i = 0; i < m; i++) {
		Vertex_handle nearest = triang.nearest_vertex(possible[i]);
		K::FT d = CGAL::squared_distance(nearest->point(), possible[i]);
		std::cout << d << '\n';
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(0);

	while(std::cin >> n) {
		if (n == 0) break;
		read();
		solve();
	}
	return 0;
}