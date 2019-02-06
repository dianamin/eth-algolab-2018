#include <iostream>
#include <vector>

#include <CGAL/Gmpq.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quotient<ET> SolT;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


int n, m;

std::vector <int> min_;
std::vector <int> max_;

std::vector <int> p;

std::vector < std::vector <int> > C;

void read() {
	min_ = std::vector <int>(n);
	max_ = std::vector <int>(n);

	p = std::vector <int>(m);
	C = std::vector < std::vector <int> >(m, std::vector <int>(n));

	for (int i = 0; i < n; i++)
		std::cin >> min_[i] >> max_[i];

	for (int j = 0; j < m; j++) {
		std::cin >> p[j];
		for (int i = 0; i < n; i++) {
			std::cin >> C[j][i];
		}
	}
}


int floor_to_double(const SolT&x) {
	double a = std::floor(CGAL::to_double(x));
	return a;
}

void solve() {
	Program lp(CGAL::SMALLER, true, 0, false, 0);

	for (int q = 0; q < m; q++)
		lp.set_c(q, p[q]);

	for (int i = 0; i < n; i++) {
		for (int q = 0; q < m; q++) {
			lp.set_a(q, i, -C[q][i]);
			lp.set_a(q, n + i, C[q][i]);
		}
		lp.set_b(i, -min_[i]);
		lp.set_b(n + i, max_[i]);
	}

	Solution sol = CGAL::solve_linear_program(lp, ET());

	if (sol.status() == CGAL::QP_INFEASIBLE) {
		std::cout << "No such diet.\n";
		return;
	}
	std::cout << floor_to_double(sol.objective_value()) << '\n';
}

int main() {
	std::ios_base::sync_with_stdio(false);

	while (std::cin >> n >> m) {
		if (n + m == 0) break;
		read();
		solve();
	}
}