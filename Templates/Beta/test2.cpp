#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 433;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    cout << "ans : " << ans << '\n';
    return ans;
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m = MOD) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
 
ll gcdExtended(ll a, ll b, ll *x, ll *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
 
    ll x1, y1;
    ll gcd = gcdExtended(b % a, a, &x1, &y1);
 
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // for(int i = 0; i < 12; i++) {
    //     // cout << "i : " << i << " g^i = " << binexp(11,i) << '\n';
    //     cout << "i : " << i << " h * g^(-i) = " << 21 * binexp(modInverse(11,MOD),i * 9) % MOD << '\n';
    // }

    // cout << binexp(11,37) << '\n';
    // cout << modInverse(19,23);
    
    // cout << binexp(64,18) << '\n';
    // cout << modInverse(59,71);
    
    // cout << binexp(166, 432/16) << '\n';
    // cout << binexp(166,) << '\n';
    // for(int i = 0; i < MOD; i++) {
    //     if(binexp(265 % MOD,i) == 335 % MOD) {
    //         cout << "I : " << i << '\n';
    //         break;
    //     }
    // }

    // binexp(250,8);
    cout << modInverse(16,27) << '\n';

    return 0;
}