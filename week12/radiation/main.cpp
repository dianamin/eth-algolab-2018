#include <iostream>
#include <vector>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpz.h>

// choose exact integral type
typedef CGAL::Gmpz ET;

// program and solution types
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;


int n;
std::vector <double> x;
std::vector <double> y;
std::vector <double> z;
std::vector <bool> is_good;

void read() {
  int h, t;
  std::cin >> h >> t;
  n = h + t;

  x = std::vector <double>(n);
  y = std::vector <double>(n);
  z = std::vector <double>(n);
  is_good = std::vector <bool>(n);

  for (int i = 0; i < h; i++) {
    std::cin >> x[i] >> y[i] >> z[i];
    is_good[i] = true;
  }

  for (int i = 0; i < t; i++) {
    std::cin >> x[h + i] >> y[h + i] >> z[h + i];
    is_good[h + i] = false;
  }
}



bool separates(int d) {
  Program lp (CGAL::EQUAL, false, 0, false, 0);

  for (int point = 0; point < n; point++) {
    double x_ = 1, y_ = 1, z_ = 1;
    int var_index = 0;
    for (int px = 0; px <= d; px++, x_ *= x[point]) {
      y_ = 1;
      for (int py = 0; py <= d; py++, y_ *= y[point]) {
        z_ = 1;
        for (int pz = 0; pz <= d; pz++, z_ *= z[point]) {
          if (px + py + pz > d) break;
          lp.set_a(var_index, point, x_ * y_ * z_);
          var_index++;
        }
      }
    }
    if (is_good[point]) {
      lp.set_b(point, 1);
      lp.set_r(point, CGAL::LARGER);
    }
    else {
      lp.set_b(point, -1);
      lp.set_r(point, CGAL::SMALLER);
    }
  }
  CGAL::Quadratic_program_options options;
  options.set_pricing_strategy(CGAL::QP_BLAND); 
  Solution s = CGAL::solve_linear_program(lp, ET(), options);
  return !s.is_infeasible();
}

void solve() {
  /*int st = 1;
  int dr = 1;
  
  do {
      dr = dr * 2;
    } while(dr <= 30 && !separable(dr));

    st = dr / 2 - 1;
    dr = std::min(dr, 30);*/

  int st = 0;
  int dr = 30;

  int sol = -1;

  while (st <= dr) {
    // std::cout << st << ' ' << dr << '\n';
    int mid = (st + dr) / 2;
    if (separates(mid)) {
      sol = mid;
      dr = mid - 1;
    }
    else st = mid + 1; 
  }

  if (sol == -1) std::cout << "Impossible!" << '\n';
  else std::cout << sol << '\n';
}

int main() {
  std::ios_base::sync_with_stdio(false);

  int t; std::cin >> t;
  while(t--) {
    read();
    solve();
  }
  return 0;
}
