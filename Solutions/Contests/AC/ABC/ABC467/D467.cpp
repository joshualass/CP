#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

void solve() {
    
    ll px, py, qx, qy, rx, ry, sx, sy; cin >> px >> py >> qx >> qy >> rx >> ry >> sx >> sy;

    auto getline = [](ll ax, ll ay, ll bx, ll by, int perp) -> array<ll,2> {
        ll dx = bx - ax;
        ll dy = by - ay;
        ll g = gcd(abs(dx), abs(dy));
        dx /= g;
        dy /= g;
        if(perp) {
            swap(dx, dy);
            dx *= -1;
        }
        if(dy < 0) {
            dx *= -1;
            dy *= -1;
        }
        if(dx < 0) {
            dx *= -1;
            dy *= -1;
        }
        return {dx, dy};
    };

    auto one = getline(px, py, qx, qy, 1);
    auto two = getline(rx, ry, sx, sy, 1);

    // cout << "one : " << one << endl;
    // cout << "two : " << two << endl;

    if(one == two) {
        ll ax = px + qx, ay = py + qy, bx = rx + sx, by = ry + sy;
        auto three = getline(ax, ay, bx, by, 0);
        // cout << "three : " << three << endl;
        if(three != one && (ax != bx || ay != by)) {
            cout << "No\n";
            return;
        }
    }

    cout << "Yes\n";


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}