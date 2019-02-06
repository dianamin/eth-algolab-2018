#include <iostream>
#include <cassert>

#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

typedef CGAL::Gmpz ET;
typedef CGAL::Quadratic_program <int> Program;
typedef CGAL::Quadratic_program_solution <ET> Solution;


typedef CGAL::Quotient<ET> SolT;

int ceil_to_double(const SolT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

int floor_to_double(const SolT&x) {
	double a = std::floor(CGAL::to_double(x));
	return a;
}

void solve_1() {
	Program qp(CGAL::SMALLER, true, 0, false, 0);

	int a, b;
	std::cin >> a >> b;

	const int X = 0;
	const int Y = 1;

	qp.set_d(X, X, 2 * a);
	qp.set_c(Y, -b);

	qp.set_a(X, 0, 1);
	qp.set_a(Y, 0, 1);
	qp.set_b(0, 4);

	qp.set_a(X, 1, 4);
	qp.set_a(Y, 1, 2);
	qp.set_b(1, a * b);

	qp.set_a(X, 2, -1);
	qp.set_a(Y, 2, 1);
	qp.set_b(2, 1);

	Solution s = CGAL::solve_quadratic_program(qp, ET());

	if (s.status() == CGAL::QP_INFEASIBLE) {
		std::cout << "no\n";
		return;
	}

	if (s.status() == CGAL::QP_UNBOUNDED) {
		std::cout << "unbounded\n";
		return;
	}

	std::cout << floor_to_double((-1) * s.objective_value()) << '\n';
}

void solve_2() {
	Program qp(CGAL::LARGER, false, 0, false, 0);

	const int X = 0;
	const int Y = 1;
	const int Z_2 = 2;

	int a, b;
	std::cin >> a >> b;

	qp.set_u(X, true, 0);
	qp.set_u(Y, true, 0);
	qp.set_l(Z_2, true, 0);

	qp.set_d(X, X, 2 * a);
	qp.set_d(Z_2, Z_2, 2);

	qp.set_c(Y, b);

	qp.set_a(X, 0, 1);
	qp.set_a(Y, 0, 1);
	qp.set_b(0, -4);

	qp.set_a(X, 1, 4);
	qp.set_a(Y, 1, 2);
	qp.set_a(Z_2, 1, 1);
	qp.set_b(1, -a * b);

	qp.set_a(X, 2, -1);
	qp.set_a(Y, 2, 1);
	qp.set_b(2, -1);

	Solution s = CGAL::solve_quadratic_program(qp, ET());


	if (s.status() == CGAL::QP_INFEASIBLE) {
		std::cout << "no\n";
		return;
	}

	if (s.status() == CGAL::QP_UNBOUNDED) {
		std::cout << "unbounded\n";
		return;
	}

	std::cout << ceil_to_double(s.objective_value()) << '\n';

}

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(0);
	int p;
	while (std::cin >> p) {
		if (p == 0) break;

		if (p == 1) solve_1();
		else solve_2();
	}

	return 0;
}
