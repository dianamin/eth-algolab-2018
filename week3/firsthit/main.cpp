#include <iostream>
#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef std::result_of<K::Intersect_2(K::Ray_2,K::Segment_2)>::type IT;

int n;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}


void fix_segment(K::Segment_2 &s, K::Segment_2 obs, const IT& o) {
	if (const K::Point_2 * op = boost::get<K::Point_2>(&*o)) {
		s = K::Segment_2(s[0], *op);
		return;
	}
	K::Segment_2 new_s;

	const K::Segment_2* t = boost::get<K::Segment_2>(&*o);
	s = K::Segment_2(s[0], obs[0]);
	if (s.has_on(obs[1])) {
		s = K::Segment_2(s[0], obs[1]);
	}
}

void solve() {
	long x1, y1, x2, y2;

	std::cin >> x1 >> y1 >> x2 >> y2;
	K::Ray_2 ray = K::Ray_2(K::Point_2(x1, y1), K::Point_2(x2, y2));
	K::Segment_2 segment = K::Segment_2(K::Point_2(x1, y1), K::Point_2(x2, y2));

	std::vector <K::Segment_2> obstacles(n);
	for (int i = 0; i < n; i++) {
		std::cin >> x1 >> y1 >> x2 >> y2;
		//std::cout << x1 << y1 << x2 << y2 << '\n';
		obstacles[i] = K::Segment_2(K::Point_2(x1, y1), K::Point_2(x2, y2));
	}
	std::random_shuffle(obstacles.begin(), obstacles.end());

	int i = 0;
	bool found = 0;
	for (; i < n; i++) {
		K::Segment_2 obstacle = obstacles[i];
		if (CGAL::do_intersect(obstacle, ray)) {
			found = true;
			//fix_segment(segment, obstacle, CGAL::intersection(ray, obstacle));
			auto o = CGAL::intersection(ray, obstacle);
			
			if (const K::Point_2 *op = boost::get<K::Point_2>(&*o)) {
				//std::cout << *op << '\n';
				segment = K::Segment_2(ray.source(), *op);
				i++;
				break;
			}
			segment = K::Segment_2(ray.source(), obstacle[0]);
			
			if (segment.has_on(obstacle[1]))
				segment = K::Segment_2(ray.source(), obstacle[1]);

			i++;
			break;
		}
	}

	if (!found) {
		std::cout << "no";
		return;
	}

	for (; i < n; i++) {
		K::Segment_2 obstacle = obstacles[i];
		if (CGAL::do_intersect(segment, obstacle))
			fix_segment(segment, obstacle, CGAL::intersection(segment, obstacle));
	}


	// check [1]

	std::cout << floor_to_double(segment[1].x()) << ' '
			  << floor_to_double(segment[1].y());
}

int main() {
	std::ios_base::sync_with_stdio(false);
  	std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

  	int i = 0;
	while(std::cin >> n) {
		//std::cout << n << ' ';
		if (n == 0) return 0;
		if (i) std::cout << '\n';
		solve();
		i++;
	}

	return 0;
}