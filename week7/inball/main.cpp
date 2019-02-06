#include <iostream>
#include <vector>

#include <CGAL/Gmpq.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int n, d;
std::vector < std::vector <int> > a;
std::vector <int> b;
std::vector <long> norm;

void read() {
	std::cin >> d;
	a = std::vector < std::vector <int> >(n, std::vector <int>(d));
	b = std::vector <int>(n);
	norm = std::vector <long>(n, 0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			std::cin >> a[i][j];
			norm[i] += a[i][j] * a[i][j];
		}
		std::cin >> b[i];
		norm[i] = std::floor(std::sqrt(norm[i]));
	}
}

void solve() {
	Program lp(CGAL::SMALLER, false, 0, false, 0);
	int R = d;

	lp.set_l(R, true, 0);
	// d + 1 vars - C0, C1, ..., Cd-1, R
	lp.set_c(R, -1);

	for (int i = 0; i < n; i++) {
		for (int c = 0; c < d; c++) {
			lp.set_a(c, i, a[i][c]);
		}
		lp.set_a(R, i, norm[i]);

		lp.set_b(i, b[i]);
	}

	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.status() == CGAL::QP_INFEASIBLE) {
		std::cout << "none\n";
		return;
	}

	if (s.status() == CGAL::QP_UNBOUNDED) {
		std::cout << "inf\n";
		return;
	}

	int sol = (-1) * CGAL::to_double(s.objective_value());
	std::cout << sol << '\n';

}


int main() {
	std::ios_base::sync_with_stdio(false);

	while(std::cin >> n) {
		if (n == 0) break;
		read();
		solve();
	}
}