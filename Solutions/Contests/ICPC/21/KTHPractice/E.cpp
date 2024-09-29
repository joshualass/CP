#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, r; cin >> n >> r;
    vector<ll> s(n), w(n);

    for(int i = 0; i < n; i++) {
        cin >> s[i];
        cin >> w[i];
    }

    ll lo = 0, hi = 1e10;

    while(lo != hi) {
        ll trymin = (lo + hi + 1) / 2;
        ll hiwater = 0;

        int ok = 1;

        for(int i = 0; i < n; i++) {
            ll waterneeded = max(0LL, trymin - s[i]);
            ll nexthi = min(r, hiwater + w[i] - waterneeded);
            if(nexthi < 0) {
                ok = 0;
            }
            hiwater = nexthi;
        }

        if(ok) {
            lo = trymin;
        } else {
            hi = trymin - 1;
        }

    }

    // cout << lo << '\n';

    ll l2 = 0, r2 = 1e10;
    while(l2 != r2) {
        ll m2 = (l2 + r2) / 2;

        ll rlo = 0, rhi = 0;
        int ok = 1;
        for(int i = 0; i < n; i++) {
            ll emax = m2 - s[i];
            ll emin = lo - s[i];
            ll nrlo = max(0LL, rlo - (emax - w[i]));
            ll nrhi = min(r, rhi + (w[i] - emin));

            if(nrlo > r || nrhi < 0) {
                ok = 0;
            }
            if(m2 == 5) {
                // cout << "i : " << i << '\n';
                // cout << "rlo : " << rlo << " rhi : " << rhi << " nrlo : " << nrlo << " nrhi : " << nrhi << '\n';
            }

            rlo = nrlo;
            rhi = nrhi;

        }

        // cout << "m2 : " << m2 << " ok : " << ok << '\n';

        if(ok && rlo == 0) {
            r2 = m2;
        } else {    
            l2 = m2 + 1;
        }

    }

    cout << l2 - lo << '\n';


    return 0;
}