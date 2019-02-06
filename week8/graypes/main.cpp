#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

#include <CGAL/Delaunay_triangulation_2.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<K> DT;
typedef DT::Edge_iterator EdgeIt;

typedef K::Point_2 P;

int n;
std::vector <P> graypes;

double ceil_to_double(EK::FT const & x) {
	double a = std::ceil(CGAL::to_double(x));
	while (a < x) a += 1;
	while (a-1 >= x) a -= 1;
	return a;
}


void read() {
	int x, y;

	graypes = std::vector <P>(n);

	for (int i = 0; i < n; i++) {
		std::cin >> x >> y;
		graypes[i] = P(x, y);
	}
}

void solve() {
	DT triang;
	triang.insert(graypes.begin(), graypes.end());

	K::FT d = std::numeric_limits<K::FT>::max();
	for (EdgeIt e = triang.finite_edges_begin();
				e != triang.finite_edges_end();
				e++) {
		d = std::min(triang.segment(*e).squared_length(), d);
	}

	EK::FT sol = CGAL::sqrt(EK::FT(d)) * 100 / 2;
	std::cout << ceil_to_double(sol) << '\n';
}


int main() {
	std::ios_base::sync_with_stdio(false);
	while(std::cin >> n) {
		if (n == 0) break;
		read();
		solve();
	}
	return 0;
}