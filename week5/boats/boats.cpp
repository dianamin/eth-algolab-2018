#include <iostream>
#include <set>

using namespace std;

int n;
set < pair <int, pair <int, int> > > s;

void read() {
    s.clear();
    
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b;
        cin >> a >> b;
        s.insert(make_pair(b, make_pair(b - a, b)));
    }
}

void solve() {
    set < pair <int, pair <int, int> > > :: iterator e = s.begin();
    int last = (*e).second.first - 1;
    int sol = 0;
    while(!s.empty()) {
        e = s.begin();
        s.erase(e);
        int a = (*e).second.first;
        int b = (*e).first;
        int ring = (*e).second.second;
        if (a < last) {
            b = last + (b - a);
            a = last;
            if (a > ring) continue;
            s.insert(make_pair(b, make_pair(a, ring)));
            continue;
        }
        sol++;
        last = b;
    }
    cout << sol << '\n';
}

int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
	while(t--) {
		read();
		solve();
	}
	return 0;
}