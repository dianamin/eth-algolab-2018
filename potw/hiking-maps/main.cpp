#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 P;

struct Triangle {
	Triangle() {}

	P points[6];
	Triangle(P points_[6]) {
		for (int i = 0; i < 6; i++) 
			points[i] = points_[i];

		for (int i = 0; i < 3; i++) {
			P a = points[2 * i];
			P b = points[2 * i + 1];

			for (int j = 0; j < 6; j++) {
				if (j == 2 * i || j == 2 * i + 1) continue;
				if (CGAL::right_turn(a, b, points[j])) {
					std::swap(a, b);
				}
			}
			points[2 * i] = a;
			points[2 * i + 1] = b;
		}
	}

	bool inside(P point) {
		for (int i = 0; i < 3; i++) {
			if (CGAL::right_turn(points[2 * i], points[2 * i + 1], point))
				return false;
		}
		return true;
	}
};

int m, n;

std::vector <P> p;
std::vector <Triangle> t;

void read() {
	std::cin >> m >> n;

	long x, y;
	p = std::vector <P>(m);
	for (int i = 0; i < m; i++) {
		std::cin >> x >> y;
		p[i] = P(x, y);
	}

	P points[6];
	t = std::vector <Triangle>(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 6; j++) {
			std::cin >> x >> y;
			points[j] = P(x, y);
		}
		t[i] = Triangle(points);
	}
}

void solve() {
	std::vector <int> contained(m - 1, 0);

	int cost = n;

	int total = 0;

	for (int b = 0, e = 0; e < n; e++) {
		// find contained legs
		for (int i = 0; i < m - 1; i++) {
			if (t[e].inside(p[i]) && t[e].inside(p[i + 1])) { //leg contained
				if (contained[i] == 0) total++;
				contained[i]++; 
			}
		}

		if (total < m - 1) continue;
		// all contained
		while (b < e) {
			// std::cout << b << ' ' << e << '\n';
			bool can_remove = true;
			for (int i = 0; i < m - 1; i++) {
				if (t[b].inside(p[i]) && t[b].inside(p[i + 1]))
					if (contained[i] == 1) can_remove = false;
			}

			if (!can_remove) break;
			for (int i = 0; i < m - 1; i++) {
				if (t[b].inside(p[i]) && t[b].inside(p[i + 1]))
					contained[i]--;
			}
			b++;
		}
		//std::cout << "ajung aici\n";

		if (e - b + 1 < cost) cost = e - b + 1;
	}

	std::cout << cost << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int c; std::cin >> c;
	while(c--) {
		read();
		solve();
	}
	return 0;
}