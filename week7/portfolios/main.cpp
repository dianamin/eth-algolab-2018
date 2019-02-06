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

int C, R, V;

std::vector <int> c;
std::vector <int> r;

std::vector < std::vector <int> > v;

void read() {
	c = std::vector <int>(n);
	r = std::vector <int>(n);

	v = std::vector < std::vector <int> >(n, std::vector <int>(n));

	for (int i = 0; i < n; i++)
		std::cin >> c[i] >> r[i];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			std::cin >> v[i][j];
}

Program qp;

void init_lp() {
	qp = Program(CGAL::SMALLER, true, 0, false, 0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++)
			qp.set_d(i, j, 2 * v[i][j]);
	}


	for (int i = 0; i < n; i++) {
		qp.set_a(i, 0, -r[i]);
		qp.set_a(i, 1, c[i]);
	}
}

void solve() {
	init_lp();

	for (int i = 0; i < m; i++) {
		std::cin >> C >> R >> V;

		qp.set_b(0, -R);
		qp.set_b(1, C);

		Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
		if (s.status() == CGAL::QP_INFEASIBLE ||
			s.status() == CGAL::QP_UNBOUNDED) {
			std::cout << "No.\n";
			continue;
		}

		if (s.objective_value() <= V)
			std::cout << "Yes.\n";
		else std::cout << "No.\n";
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);

	while (std::cin >> n >> m) {
		if (n + m == 0) break;
		read();
		solve();
	}
	return 0;
}
