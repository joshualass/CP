#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, q; cin >> n >> m >> q;
    ll A = 0, B = 0;
    set<ll> a, b;
    for(ll i = 0; i < n; i++) {
        ll x; cin >> x;
        A += x;
        a.insert(x);
    }
    for(ll i = 0; i < m; i++) {
        ll x; cin >> x;
        B += x;
        b.insert(x);
    }

    const ll mx = 2e5;

    ll S = A * B;
    ll min_delt = -mx, max_delt = mx;
    // cout << "S : " << S << " A : " << A << " B : " << B << " min_delt : " << min_delt << " max_delt : " << max_delt << '\n';
    vector<ll> poss(mx * 2 + 1);
    for(ll x : a) {
        if(x - A == 0) {
            continue;
        }
        ll p = x - A;
        // ll b0 = (min_delt + x * B) / p, b1 = (max_delt + x * B) / p;
        ll b0 = (min_delt - S + B * x) / p, b1 = (max_delt - S + B * x) / p;
        ll lo_b = min(b0,b1) - 5;
        ll hi_b = max(b0,b1) + 5;
        // cout << "lo_b : " << lo_b << '\n';
        set<ll>::iterator it = b.lower_bound(lo_b);
        while(it != b.end() && (*it) <= hi_b) {
            ll v = S + -x * B + (*it) * p + mx;
            if(v >= 0 && v <= mx * 2) {
                poss[v] = 1;
            }
            it++;
        }
    }

    for(ll i = 0; i < q; i++) {
        ll x; cin >> x;
        cout << (poss[x+mx] ? "Yes" : "No") << '\n';
    }

    return 0;
}