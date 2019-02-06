#include <iostream>
#include <vector>

#include <CGAL/Gmpq.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> objective_t;

int n, m, h, w;

std::vector < std::pair <int, int> > nail;
std::vector < std::pair <int, int> > old_nail;

double ceil_to_double( objective_t const & o) {
 double d = std::ceil( CGAL::to_double( o ) );
 while( d < o ) d += 1;
 while( d-1 >= o ) d -= 1;
 return d;
}

void read() {
	std::cin >> n >> m >> h >> w;
	nail = std::vector < std::pair <int, int> >(n);
	old_nail = std::vector < std::pair <int, int> >(m);

	for (int i = 0; i < n; i++)
		std::cin >> nail[i].first >> nail[i].second;

	for (int i = 0; i < m; i++)
		std::cin >> old_nail[i].first >> old_nail[i].second;
}

void solve() {
	Program lp(CGAL::SMALLER, true, 1, false, 0);

	for (int alpha = 0; alpha < n; alpha++)
		lp.set_c(alpha, -2 * (h + w));

	int id = 0;
	for (int alpha1 = 0; alpha1 < n; alpha1++) {
		for (int alpha2 = alpha1 + 1; alpha2 < n; alpha2++) {

			std::pair <int, int> a1 = nail[alpha1];
			std::pair <int, int> a2 = nail[alpha2];
			ET dx_ = std::abs(a1.first - a2.first);
			ET dy_ = std::abs(a1.second - a2.second);

			lp.set_a(alpha1, id, 1);
			lp.set_a(alpha2, id, 1);
			lp.set_b(id, 2 * std::max(dx_ / w, dy_ / h));
			id++;
		}
	}

	if (m != 0) {
		for (int alpha1 = 0; alpha1 < n; alpha1++) {
			ET limit = 33554432;

			for (int alpha2 = 0; alpha2 < m; alpha2++) {
				std::pair <int, int> a1 = nail[alpha1];
				std::pair <int, int> a2 = old_nail[alpha2];

				ET dx_ = std::abs(a1.first - a2.first);
				ET dy_ = std::abs(a1.second - a2.second);

				limit = std::min(limit, 2 * std::max(dx_ / w, dy_ / h) - 1);
			}

			lp.set_a(alpha1, id, 1);
			lp.set_b(id, limit);
			id++;
		}
	}

	Solution s = CGAL::solve_linear_program(lp, ET());

	long long sol = ceil_to_double(CGAL::to_double((-1) * s.objective_value()));
	std::cout << sol << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t; 
	std::cin >> t;
	while (t--) {
		read();
		solve();
	}
	return 0;
}
