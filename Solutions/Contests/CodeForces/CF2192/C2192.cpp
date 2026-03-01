#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

void solve() {
    
    ll n, h, k; cin >> n >> h >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll cycles = h / accumulate(a.begin(), a.end(), 0LL);
    h -= cycles * accumulate(a.begin(), a.end(), 0LL);

    ll l = 0, r = n;
    while(l != r) {
        // cout << "l : " << l << " r : " << r << endl;
        ll m = (l + r) / 2;
        ll ok;
        if(m == 0) {
            ok = h == 0;
        } else {
            ll lo = *min_element(a.begin(), a.begin() + m), hi = *max_element(a.begin() + m, a.end());
            ll d = (hi > lo ? hi - lo : 0LL);
            ll s = accumulate(a.begin(), a.begin() + m, 0LL) + d;
            ok = s >= h;
        }
        if(ok) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l + cycles * n + max(0LL, cycles - (h == 0)) * k << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}