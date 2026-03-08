#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<ld,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    auto _work = [&](ld time) -> ld {
        ld lo = LLONG_MAX, hi = LLONG_MIN;
        for(auto [x, v] : a) {
            ld pos = x + v * time;
            lo = min(lo, pos);
            hi = max(hi, pos);
        }
        return hi - lo;
    };

    ld l = 0, r = 1e14;
    while(r - l > 1e-9) {
        ld m1 = l + (r - l) / 3, m2 = l + (r - l) / 3 * 2;
        ld d1 = _work(m1), d2 = _work(m2);
        if(d1 < d2) {
            r = m2;
        } else {
            l = m1;
        }
    }

    cout << fixed << setprecision(10) << _work(l) << '\n';

    return 0;
}
