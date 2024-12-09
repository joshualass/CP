#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll binexp(ll base, ll power, ll mod = MOD) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%mod;
        }
        base = base*base%mod;
        power >>= 1;
    }
    return ans;
}


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll p, g, h; cin >> p >> g >> h;
    for(ll i = 1; i < p; i++) {
        if(binexp(g,i,p) == h) {
            cout << "x = " << i << '\n';
            return 0;
        }
    }

    cout << "solution not found\n";

    return 0;
}

/*
19079 17 2
*/