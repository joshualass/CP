#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll res = a[0], lo = a[0], hi = a[0];

    auto try_cand = [&](ll curr_sum, ll cand, ll &nxlo, ll &nxhi) -> void {
        res = max(res, cand);
        nxlo = min(nxlo, curr_sum + cand);
        nxhi = max(nxhi, curr_sum + cand);
    };

    auto work = [&](ll curr_sum, ll ai, ll &nxlo, ll &nxhi) -> void {
        try_cand(curr_sum, ai, nxlo, nxhi);
        try_cand(curr_sum, ai-curr_sum, nxlo, nxhi);
        try_cand(curr_sum, ai+curr_sum, nxlo, nxhi);
    };

    for(ll i = 1; i < n; i++) {
        ll nx_lo = LLONG_MAX, nx_hi = LLONG_MIN;
        work(lo, a[i], nx_lo, nx_hi);
        work(hi, a[i], nx_lo, nx_hi);
        lo = nx_lo;
        hi = nx_hi;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    for(ll i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}