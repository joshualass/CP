#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1889570071;

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

    // cout << binexp(36,19) << '\n';
    // cout << modInverse(137, 540) << '\n';
    // cout << binexp(428, 473) << '\n';
    // cout << binexp(213,137) << '\n';
    // cout << modInverse(73, 1080) << '\n';
    // cout << binexp(614, 577) << '\n';
    // cout << binexp(158, 73) << '\n';
    // cout << binexp(892383, 103) << '\n';
    // cout << modInverse(103,2035800) << '\n';
    // cout << binexp(45293, 810367) << '\n';

    // cout << binexp(modInverse(1244183534),97163003) * binexp(732959706,164932134) % MOD << '\n';
    // // cout << -97163003LL * 1244183534LL + 164932134LL * 732959706LL << '\n';
    // for(ll i = 1; i < MOD; i++) {
    //     if(i * i % MOD == 1341261000) {
    //         cout << i << '\n';
    //         break;
    //     }
    // }   

    // cout << "done\n";
    // cout << binexp(652581659,)
    // cout << binexp(1244183534,252426389) * binexp(modInverse(732959706),496549570) % MOD << '\n';
    cout << binexp(1054592380,519424709) << '\n';

    return 0;
}