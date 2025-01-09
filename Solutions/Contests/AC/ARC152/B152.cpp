#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, l; cin >> n >> l;
    set<ll> s;
    s.insert(inf);
    s.insert(-inf);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        s.insert(x);
    }

    ll res = LLONG_MAX;

    for(ll x : s) {
        if(abs(x) != inf) {
            ll mid = abs(l - x);
            // cout << "x : " << x << " lb : " << (*s.lower_bound(mid)) << " --lb : " << (*--s.lower_bound(mid)) << '\n';
            ll wait = min(*s.lower_bound(mid) - mid, mid - *--s.lower_bound(mid));
            res = min(res, (wait + l) * 2);
        }
    }

    cout << res << '\n';

    return 0;
}