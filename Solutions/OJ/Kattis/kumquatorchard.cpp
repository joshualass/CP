#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
    }

    auto rotate = [&](array<ld,4> b) -> array<ld,4> {
        return {b[1], -b[2], b[3], -b[0]};
    };

    auto test = [&](vector<array<ld,4>> &b) -> int {
        for(auto [x, y] : a) {
            int f = 0;
            for(auto [x0, y0, x1, y1] : b) {
                if(x0 < x && x < x1 && y0 < y && y < y1) {
                    f = 1;
                }
            }
            if(f == 0) return 0;
        }
        return 1;
    };

    vector<array<ld,4>> first = {
        {-1000.1, 0.9, 1000.1, 1000.1}
    };

    vector<array<ld,4>> second = {
        {-1000.1, 0.9, 1000.1, 1000.1},
        {-1000.1, -1000.1, 1000.1, -0.9}
    };

    vector<array<ld,4>> second2 = {
        {-1000.1, 0.9, 1000.1, 1000.1},
        {0.9, -1000.1, 1000.1, 0.1}
    };

    vector<array<ld,4>> third = {
        {-1000.1, 0.9, 1000.1, 1000.1},
        {0.9, -1000.1, 1000.1, 0.1},
        {-1000.1, -1000.1, -0.9, 0.1}
    };

    vector<array<ld,4>> fourth = {
        {-1000.1, 0.9, 1000.1, 1000.1},
        {0.9, -1000.1, 1000.1, 0.1},
        {-1000.1, -1000.1, -0.9, 0.1},
        {-0.1, -1000.1, 0.1, -0.9}
    };

    vector<vector<array<ld,4>>> together = {
        first, second, second2, third, fourth
    };

    for(auto &x : together) {
        for(int i = 0; i < 4; i++) {
            if(test(x)) {
                cout << sz(x) << endl;
                for(auto [x0, y0, x1, y1] : x) {
                    cout << x0 << " " << y0 << " " << x1 << " " << y0 << " " << x1 << " " << y1 << " " << x0 << " " << y1 << endl;
                }
                return 0;
            }
            for(auto &y : x) {
                y = rotate(y);
            }
        }
    }

    assert(0);

    return 0;
}
