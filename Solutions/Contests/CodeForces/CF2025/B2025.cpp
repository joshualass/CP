#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll t; cin >> t;
    for(int i = 0; i < t; i++) {
        int tt; cin >> tt;
    }
    for(int i = 0; i < t; i++) {
        ll k; cin >> k;
        cout << binexp(2,k) << '\n';
    }

    return 0;
}