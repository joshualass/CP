#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

void solve() {
    ll n; cin >> n;
    ll a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;

    auto solve = [](array<ll,3> l, array<ll,3> r) -> ll {
        ll res = 0;
        for(ll i = 0; i < 3; i++) {
            ll sub = min(l[i], r[(i+1) % 3]);
            res += sub;
            l[i] -= sub;
            r[(i + 1) % 3] -= sub;
        }
        for(ll i = 0; i < 3; i++) {
            ll sub = min(l[i], r[i]);
            l[i] -= sub;
            r[i] -= sub;
        }
        res -= accumulate(l.begin(), l.end(), 0);
        return res;
    };

    cout << solve({a, b, c}, {d, e, f}) << " " << -solve({d, e, f}, {a, b, c}) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}