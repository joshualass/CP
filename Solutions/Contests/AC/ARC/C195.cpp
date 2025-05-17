#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int r, b; cin >> r >> b;

    if((r & 1) || (r == 0 && (b & 1))) {
        cout << "No\n";
        return;
    }

    vector<pair<array<int,2>,char>> res;
    int cx = 0, cy = 0;

    auto add = [&](int dx, int dy) -> void {
        char c = (abs(dx) + abs(dy) == 2 ? 'B' : 'R');
        res.push_back({{cx, cy}, c});
        cx += dx;
        cy += dy;
    };

    if(b) {
        int rem = b - 1;
        int up = rem / 2;
        int down = (rem + 1) / 2;

        for(int i = 0; i < up; i++) {
            add(1, 1);
        }
        add(-1, 1);
        for(int i = 0; i < down; i++) {
            add(-1, -1);
        }
    }

    if(r) {
        r -= 2;
        add(-1 - cx, 0 - cy);

        for(int i = 0; i < r / 2; i++) {
            add(0,-1);
        }
        add(1, 0);
        for(int i = 0; i < r / 2; i++) add(0, 1);
    }

    cout << "Yes\n";
    for(auto [x, c] : res) {
        cout << c << " " << x[0] + 1000000 << " " << x[1] + 1000000 << '\n';
        // cout << x[0] << " " << x[1] << " " << c << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}