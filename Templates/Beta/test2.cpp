#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 23;

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

    cout << binexp(2,51) << '\n';

    return 0;
}