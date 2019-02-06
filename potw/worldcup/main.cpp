#include <iostream>
#include <vector>

#include <CGAL/Gmpq.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>


#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>


typedef CGAL::Gmpq ET;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;
typedef CGAL::Quotient<ET> objective_t;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  DT;

typedef K::Point_2 Point;

double floor_to_double( objective_t const & o) {
 double d = std::floor( CGAL::to_double( o ) );
 while( d < o ) d += 1;
 while( d-1 >= o ) d -= 1;
 return d;
}

struct Warehouse {
	long x, y, s, a;
	Point p;
};

struct Stadium {
	long x, y, d, u;
	Point p;

};

struct ContourLine {
	long x, y, r;
	Point p;

	
	bool sgn(long x) {
		return x > 0;
	}

	bool intersects(Warehouse w, Stadium s) {
		long d_w = (x - w.x) * (x - w.x) + (y - w.y) * (y - w.y) - r;
		long d_s = (x - s.x) * (x - s.x) + (y - s.y) * (y - s.y) - r;

		return sgn(d_w) != sgn(d_s);
	}
};

int n, m, p;

std::vector <Warehouse> w;
std::vector <Stadium> s;
std::vector <ContourLine> c;
std::vector < std::vector <int> > r;
std::vector < std::vector <ET> > R;
std::vector < std::vector <int> > A;

std::vector <Point> points;

void read() {
	std:: cin >> n >> m >> p;

	w = std::vector <Warehouse>(n);
	s = std::vector <Stadium>(m);
	c = std::vector <ContourLine>(p);

	r = std::vector < std::vector <int> >(n, std::vector <int>(m));

	points = std::vector <Point>(n + m);

	for (int i = 0; i < n; i++) {
		std::cin >> w[i].x >> w[i].y >> w[i].s >> w[i].a;
		w[i].p = Point(w[i].x, w[i].y);
		points[i] = w[i].p;
	}

	for (int i = 0; i < m; i++) {
		std::cin >> s[i].x >> s[i].y >> s[i].d >> s[i].u;
		s[i].p = Point(s[i].x, s[i].y);
		points[n + i] = s[i].p;
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			std::cin >> r[i][j];

	for (int i = 0; i < p; i++) {
		std::cin >> c[i].x >> c[i].y >> c[i].r;
		c[i].p = Point(c[i].x, c[i].y);
		c[i].r *= c[i].r;
	}
}

void compute_R_A() {
	R = std::vector < std::vector <ET> >(n, std::vector <ET>(m));
	A = std::vector < std::vector <int> >(n, std::vector <int>(m));
	int ind = 0;

	std::vector <int> cidx;
	DT dt(points.begin(), points.end());
	for (int k = 0; k < p; k++) {
		DT::Vertex_handle nearest_point = dt.nearest_vertex(c[k].p);
		if (CGAL::squared_distance(nearest_point->point(), c[k].p) < c[k].r) {
			cidx.push_back(k);
		}
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			int t = 0;
			A[i][j] = ind++;
			for (int k = 0; k < cidx.size(); k++)
				if (c[cidx[k]].intersects(w[i], s[j])) t++;
			R[i][j] = ET(r[i][j]) - ET(t) / 100;
		}
}

void solve() {
	compute_R_A();

	Program lp(CGAL::SMALLER, true, 0, false, 0);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			lp.set_u(A[i][j], true, w[i].s); // max the amount in the warehouse
			lp.set_c(A[i][j], -R[i][j]);
			//lp.set_c(A[i][j], -1);
		}

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			lp.set_a(A[i][j], j, 1);
			lp.set_a(A[i][j], j + m , ET(w[i].a) / 100);
		}
		lp.set_b(j, s[j].d);
        lp.set_r(j, CGAL::EQUAL);
		//std::cout << s[j].d;
		lp.set_b(j + m, s[j].u);
	}

	int crt = m * 2;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			lp.set_a(A[i][j], crt, 1);
		}
		lp.set_b(crt, w[i].s);

		crt++;
	}

	Solution s = CGAL::solve_linear_program(lp, ET());
	if (s.status() == CGAL::QP_INFEASIBLE) {
		std::cout << "RIOT!\n";
		return;
	}

	if (s.status() == CGAL::QP_UNBOUNDED) {
		std::cout << "RIOT!\n";
		return;
	}

	long sol = (-1) * floor_to_double(s.objective_value());
	std::cout << sol << '\n';
	//std::cout << "RIOT!\n";
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