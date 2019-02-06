#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Delaunay;
typedef K::Point_2 P;

typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

int a, s, b, e;

std::vector < std::pair <P, int> > ast;
std::vector < std::pair <P, int> > sh;
std::vector <P> bh;

void read() {
	std::cin >> a >> s >> b >> e;

	ast = std::vector < std::pair <P, int> >(a);
	sh = std::vector < std::pair <P, int> >(s);
	bh = std::vector <P>(b);

	for (int i = 0; i < a; i++) {
		int x, y, d;
		std::cin >> x >> y >> d;
		ast[i] = std::make_pair(P(x, y), d);
	}

	for (int i = 0; i < s; i++) {
		int x, y;
		std::cin >> x >> y;
		sh[i] = std::make_pair(P(x, y), 1 << 20);
	}

	for (int i = 0; i < b; i++) {
		int x, y;
		std::cin >> x >> y;
		bh[i] = P(x, y);
	}
}

void solve() {
	Delaunay d;
	d.insert(bh.begin(), bh.end());

	Program lp(CGAL::LARGER, true, 0, false, 0);

	for (int i = 0; i < s; i++) {
		lp.set_c(i, 1);
		if (b == 0) continue;
		Delaunay::Vertex_handle v = d.nearest_vertex(sh[i].first);
		sh[i].second = CGAL::squared_distance(sh[i].first, v->point());
	}

	for (int i = 0; i < a; i++) {
		for (int j = 0; j < s; j++) {
			K::FT d = CGAL::squared_distance(ast[i].first, sh[j].first);
			if (d >= sh[j].second) continue;
			if (d == 0) lp.set_a(j, i, 1);
			else lp.set_a(j, i, 1 / ET(d));
		}
		lp.set_b(i, ast[i].second);
	}

	Solution sol = CGAL::solve_linear_program(lp, ET());
	if (sol.is_infeasible() || sol.objective_value() > e)
		std::cout << "n\n";
	else std::cout << "y\n";
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int t;
	std::cin >> t;

	while(t--) {
		read();
		solve();
	}

	return 0;
}