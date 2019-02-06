#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>

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

		p[i] = (K::Point_2(x, y));
	}
}

void solve() {
	MinCircle mc(p.begin(), p.end(), true);
	K::FT r = mc.circle().squared_radius();

	for (auto it = mc.support_points_begin(); it != mc.support_points_end(); it++) {
		K::Point_2 p_crt = *it;
		
		for (int index = 0; index < n; index++) {
			if (p[index] != p_crt) continue;
			if (index == 0) p[index] = p[1];
			else p[index] = p[0];

			MinCircle mc_new(p.begin(), p.end(), true);
			K::FT r_new = mc_new.circle().squared_radius();

			p[index] = p_crt;

			if (r_new < r) r = r_new;
			break;
		}
	}

	std::cout << ceil(sqrt(r)) << '\n';
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