#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;

    map<int, set<int>> ttfang;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        ttfang[x].insert(y);
    }

    int ax;
    for(auto [x, s] : ttfang) {
        if(s.size() & 1) ax = x;
    }

    auto toggle = [&](int x, int y) -> void {
        int nx = ax;
        int ny = y + x - nx;
        if(ttfang[nx].count(ny)) {
            ttfang[nx].erase(ny);
        } else {
            ttfang[nx].insert(ny);
        }
    };

    for(auto [x, s] : ttfang) {
        if(x != ax) {
            for(int y : s) {
                toggle(x, y);
            }
        }
    }

    cout << ax << " " << *ttfang[ax].begin() << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}