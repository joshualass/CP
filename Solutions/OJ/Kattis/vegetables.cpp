#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ld t; cin >> t;
    t += 0.00005;
    multiset<array<ld,3>> ms; //{size, veg, cur chops}
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        array<ld,3> a = {x, x, 1};
        ms.insert(a);
    }

    int total_chops = 0;
    auto check = [&]() -> int {
        auto lo = *ms.begin(), hi = *--ms.end();
        return lo[0] / hi[0] > t;
    };

    while(check() == 0) {
        auto info = *--ms.end();
        ms.erase(ms.find(info));
        auto [ratio, veg, cur_chops] = info;
        array<ld,3> nx = {veg / (cur_chops + 1), veg, cur_chops + 1};
        total_chops++;
        ms.insert(nx);
    }

    cout << total_chops << '\n';

    return 0;
}
