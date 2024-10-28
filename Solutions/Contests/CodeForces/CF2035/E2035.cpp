#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
typedef __int128_t lll;
const ll MOD = 998244353;

void solve() {
    ll _x, _y, _z, _k; cin >> _x >> _y >> _z >> _k;
    lll x = _x, y = _y, z = _z, k = _k;

    auto getcost = [](lll initcost, lll attack_level, lll hpleft, lll y) -> lll {
        if(hpleft <= 0) {
            return initcost;
        }
        return initcost + ((hpleft + attack_level - 1) / attack_level) * y;
    };

    auto findmin = [&](lll waves) -> lll {
        lll cost = waves * (x * k + y);
        lll d = waves * k;
        lll hpleft = z - (waves * (waves + 1) / 2) * k;

        lll l2 = 0, r2 = k;

        while(r2 - l2 >= 100) {
            lll m1 = l2 + (r2-l2) / 3;
            lll m2 = l2 + (r2-l2) * 2 / 3;

            lll m1c = getcost(cost + m1 * x, d + m1, hpleft, y);
            lll m2c = getcost(cost + m2 * x, d + m2, hpleft, y);

            if(m1c <= m2c) {
                r2 = m2;
            } else {
                l2 = m1;
            }

        }

        lll lo = LLONG_MAX;
        for(lll j = (waves == 0 ? max((lll) 1, l2) : l2); j <= r2; j++) {
            // cout << "waves : " << (ll) waves << " j : " << (ll) j << " cost : " << (ll) getcost(cost + j * x, d + j, hpleft, y) << '\n';
            // cout << "one : " << (ll)( cost + j * x) << " two : " << (ll) (d + j) << " hpleft : " << (ll) hpleft << " y : " << (ll) y << '\n';
            lo = min(lo, getcost(cost + j * x, d + j, hpleft, y));
        }
        return lo;
    };

    lll res = LLONG_MAX;
    for(lll j = 0; j <= 5e4; j++) {
        // cout << "j : " << (ll) j << " min1 : " << (ll) findmin(j) << '\n';
        res = min(res, findmin(j));
    }

    cout << (ll) res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}