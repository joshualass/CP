#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll d; cin >> d;

    ll ans = LLONG_MAX;

    for(ll i = 0; i < 2e6; i++) {
        ll lo = 0, hi = 2e6; 
        while(lo != hi) {
            ll m = (lo + hi + 1) / 2;
            if(m * m + i * i <= d) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }
        
        ans = min(ans, abs(i * i + lo * lo - d));
        ans = min(ans, abs(i * i + (lo + 1) * (lo + 1) - d));
    }
    cout << ans << '\n';
    return 0;
}