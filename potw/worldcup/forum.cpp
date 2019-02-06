#include <bits/stdc++.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <CGAL/Gmpq.h>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  DT;

typedef CGAL::Gmpq ET;

typedef CGAL::Quotient<ET> SolT;
typedef CGAL::Quadratic_program<ET> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void testcase();

int main() {
    ios_base::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) testcase();
    return 0;
}

struct Ware { K::Point_2 p; int s, a; };
struct Stad { K::Point_2 p; int d, u; };
struct Cont { K::Point_2 p; long r;   };

double floor_to_double(const SolT& x) {
    double a = std::floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

void testcase() {

    int N, M, C; cin >> N >> M >> C;

    vector<K::Point_2> points(N+M);

    vector<Ware> wares(N);
    for (int i=0; i<N; i++) {
        long x, y; cin >> x >> y;
        wares[i].p = K::Point_2(x,y);
        cin >> wares[i].s >> wares[i].a;
        points[i] = wares[i].p;
    }

    vector<Stad> stads(M);
    for (int i=0; i<M; i++) {
        long x, y; cin >> x >> y;
        stads[i].p = K::Point_2(x,y);
        cin >> stads[i].d >> stads[i].u;
        points[N+i] = stads[i].p;
    }

    vector<vector<ET> > revs(N, vector<ET>(M));
    for (int w=0; w<N; w++) {
        for (int s=0; s<M; s++) {
            cin >> revs[w][s];
        }
    }

    vector<Cont> conts(C);
    for (int i=0; i<C; i++) {
        long x, y, r; cin >> x >> y >> r;
        conts[i].p = K::Point_2(x,y);
        conts[i].r = r*r; 
    }

    // find the (at most 100) contour lines that contain a stadium
    // or a warehouse in their interior
    vector<int> cidx;

    // points contains both warehouses and stadiums
    DT dt (points.begin(), points.end());

    for(int c=0; c<C; c++) {
        DT::Vertex_handle nn = dt.nearest_vertex(conts[c].p); 

        if (CGAL::squared_distance(nn->point(), conts[c].p) < conts[c].r) {
            cidx.push_back(c);
        }
    }
    
    for (int c : cidx) {
        K::FT R = conts[c].r; // radious is already squared

        for(int w=0; w<N; w++) {
            K::FT sdw = CGAL::squared_distance(conts[c].p, wares[w].p);
            for(int s=0; s<M; s++) {
                K::FT sds = CGAL::squared_distance(conts[c].p, stads[s].p);

                // the countour line affects the path iff one of the
                // two is in the interior and the other not
                if ((sdw <= R && sds >= R) || (sds <= R && sdw >= R)) {
                    revs[w][s] -= 0.01;
                }
            }
        }
    }
    

    Program lp (CGAL::SMALLER, true, 0, false, 0);

    // variable is the number of liter for each pair
    // (warehouse,stadium) L_w_s = w*M + s
    
    int cc = 0;

    // supply cannot be exceeded
    for(int w=0; w<N; w++) {
        for (int s=0; s<M; s++) {
            int Lws = w*M + s;
            lp.set_a(Lws, cc,  1);
        }
        lp.set_b(cc, wares[w].s);
        cc++;
    }

    // demand must be satisfied
    for (int s=0; s<M; s++) {
        for(int w=0; w<N; w++) {
            int Lws = w*M + s;
            lp.set_a(Lws, cc,  1);
        }
        lp.set_b(cc, stads[s].d);
        lp.set_r(cc, CGAL::EQUAL);
        cc++;
    }

    // alcol cannot be exceeded
    for (int s=0; s<M; s++) {
        for(int w=0; w<N; w++) {
            int Lws = w*M + s;
            lp.set_a(Lws, cc,  wares[w].a);
        }
        lp.set_b(cc, stads[s].u * 100);
        cc++;
    }

    // minimize -profit
    for (int s=0; s<M; s++) {
        for(int w=0; w<N; w++) {
            int Lws = w*M + s;
            lp.set_c(Lws, -revs[w][s]);
        }
    }

    // solve the program, using ET as the exact type
    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    if (s.is_optimal()) {
        SolT res = -s.objective_value();
        cout << (long) floor_to_double(res) << endl;
    } else {
        cout << "RIOT!" << endl;
    }

}