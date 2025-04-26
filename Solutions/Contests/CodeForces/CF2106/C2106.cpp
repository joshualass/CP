#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, k; cin >> n >> k;
    ll lo = 0, hi = k * 2;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;
    for(int i = 0; i < n; i++) {
        array<ll,2> rn = {0,0};
        if(a[i] == -1) {
            rn[1] += k;
        } else {
            rn[0] += a[i];
            rn[1] += a[i];
        }
        if(b[i] == -1) {
            rn[1] += k;
        } else {
            rn[0] += b[i];
            rn[1] += b[i];
        }
        lo = max(lo, rn[0]);
        hi = min(hi, rn[1]);
    }

    cout << max(0LL, hi - lo + 1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}