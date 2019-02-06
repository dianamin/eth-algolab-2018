#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

int n;
K::Ray_2 laser;
std::vector <K::Segment_2> obstacles;

void read() {
	obstacles = std::vector <K::Segment_2>(n);

	long x1, y1, x2, y2;

	std::cin >> x1 >> y1 >> x2 >> y2;
	laser = K::Ray_2(K::Point_2(x1, y1), K::Point_2(x2, y2));

	for (int i = 0; i < n; i++) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		obstacles[i] = K::Segment_2(K::Point_2(x1, y1), K::Point_2(x2, y2));
	}
}

void solve() {
	for (int i = 0; i < n; i++) {
		if (CGAL::do_intersect(laser, obstacles[i])) {
			std::cout << "yes\n";
			return;
		}
	}
	std::cout << "no\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);

	while(std::cin >> n) {
		if (n == 0) return 0;
		read();
		solve();
	}
	return 0;
}