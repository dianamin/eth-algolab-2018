#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2 <K> Traits;
typedef CGAL::Min_circle_2 <Traits> MinCircle;


int n;

std::vector <K::Point_2> p;

void read() {
	p = std::vector <K::Point_2>(n);

	long x, y;
	for (int i = 0; i < n; i++) {
		std::cin >> x >> y;

		p[i] = K::Point_2(x, y);
	}
}

void solve() {
	MinCircle mc(p.begin(), p.end(), true);

	Traits::Circle c = mc.circle();
	std::cout << ceil(sqrt(c.squared_radius())) << '\n';
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