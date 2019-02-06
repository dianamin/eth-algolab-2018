#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n;
vector <int> b_time;
vector <int> deactivated;
vector < pair <int, int> > sorted_balls;

int crt_b_time;

bool can_deactivate(int index) {
    if (deactivated[index] == 1) return true;
    if (deactivated[index] == -1) return false;

    if (index >= ((n - 1) / 2)) {
        if (b_time[index] > crt_b_time) {
            deactivated[index] = 1;
            crt_b_time++;
            return true;
        }
        deactivated[index] = -1;
        return false;
    }

    bool left, right;
    int left_index = 2 * index + 1;
    int right_index = 2 * index + 2;

    if (b_time[left_index] < b_time[right_index]) {
        left = can_deactivate(left_index);
        right = can_deactivate(right_index);
    }
    else {
        right = can_deactivate(right_index);
        left = can_deactivate(left_index);
    }

    if (!left || !right) {
        deactivated[index] = -1;
        return false;
    }

    if (b_time[index] > crt_b_time) {
        deactivated[index] = 1;
        crt_b_time++;
        return true;
    }

    deactivated[index] = -1;
    return false;
}

void read() {
    cin >> n;
    b_time = vector <int>(n);
    for (int i = 0; i < n; i++) {
        cin >> b_time[i];
    }
}

void solve() {
    sorted_balls = vector < pair <int, int> >(n);
    deactivated = vector<int>(n, 0);
    for (int i = 0; i < n; i++) {
        sorted_balls[i].first = b_time[i];
        sorted_balls[i].second = i;
    }
    sort(sorted_balls.begin(), sorted_balls.end());

    crt_b_time = 0;
    bool sol = true;
    for (int i = 0; i < n; i++)
        sol &= can_deactivate(sorted_balls[i].second);

    if (sol) cout << "yes\n";
    else cout << "no\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int t;
    std::cin >> t;
    while(t--) {
       // cout << t << ' ';
        read();
        solve();
    }
    return 0;
}