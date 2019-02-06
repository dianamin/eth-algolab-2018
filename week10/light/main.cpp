#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/basic.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Point_set_2.h>
#include <iostream>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;

typedef K::Point_2 Point;
typedef K::Circle_2 Circle;

typedef CGAL::Triangulation_vertex_base_with_info_2<int, K> Vb;
typedef CGAL::Triangulation_data_structure_2<Vb> Tds;
typedef CGAL::Point_set_2<K, Tds> PSet;
typedef CGAL::Point_set_2<K, Tds>::Vertex_handle Vertex_handle;


int n, m;
int h;
std::vector <Point> participant;
std::vector <int> r;
std::vector < std::pair <K::Point_2, int> > lamp;
void read() {
	std::cin >> m >> n;
	participant = std::vector <Point>(m);
	r = std::vector <int>(m);
	for (int i = 0; i < m; i++) {
		int x, y, r_;
		std::cin >> x >> y >> r_;

		participant[i] = Point(x, y);
		r[i] = r_;
	}

	std::cin >> h;
	lamp = std::vector < std::pair <K::Point_2, int> >(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		std::cin >> x >> y;
		lamp[i] = std::make_pair(Point(x, y), i);
	}
}

void solve() {
	PSet lamps_triang(lamp.begin(), lamp.end());
	std::vector<int> killer_time(m, std::numeric_limits<int>::max());


	for(int i = 0; i < m; i++) {
		Point p = participant[i];

		double d_to_kill = (double(r[i]) + double(h));
		d_to_kill *= d_to_kill;

		//std::cout << d_to_kill << '\n';
		Vertex_handle closest_lamp = lamps_triang.nearest_neighbor(p);

		if (d_to_kill <= squared_distance(closest_lamp->point(), p)) continue;

		for (int j = 0; j < n; j++) {
			if (d_to_kill > squared_distance(lamp[j].first, p)) {
				killer_time[i] = lamp[j].second;
				break;
			}
		}
	}

	int winning_time = -1;
    for (int i = 0; i < m; i++) {
    	winning_time = std::max(winning_time, killer_time[i]);
    }


    std::vector <int> sol;
    for (int i = 0; i < m; i++) {
    	if (killer_time[i] == winning_time) {
    		sol.push_back(i);
    	}
    }

    std::sort(sol.begin(), sol.end());
    for (int i = 0; i < sol.size(); i++)
    	std::cout << sol[i] << ' ';
    std::cout << '\n';
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