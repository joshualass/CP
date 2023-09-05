#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll MOD = 1e9 + 7;

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
 
ll modDivide(ll a, ll b) {
    a = a % MOD;
    int inv = modInverse(b, MOD);
    return (inv * a) % MOD;
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

ll binexp(ll base, ll power, ll MOD = 1e9 + 7) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll L, R; cin >> L >> R;
    ll l = (L + 1) / 2;
    ll r = (R + 1) / 2 + 1;

    ll fiveL = binexp(5,l);
    ll fiveR = binexp(5,r);
    // cout << "fiveL: " << fiveL << " fiveR: " << fiveR << "\n";
    ll fiveAns = modDivide((fiveR - fiveL), 4);
    // cout << "fiveAns: " << fiveAns << "\n";
    fiveAns = fiveAns * 2 % MOD;
    // cout << "fiveAns * 2: " << fiveAns << "\n";

    ll twoL = binexp(2,l);
    ll twoR = binexp(2,r);
    // cout << "twoL: " << twoL << " twoR: " << twoR << "\n";
    ll twoAns = modDivide((twoR - twoL), 1);
    // cout << "twoAns: " << twoAns << "\n";
    twoAns = twoAns * 2 % MOD;
    // cout << "twoAns * 2: " << twoAns << "\n";    
    // cout << "twoAns: " << twoAns << " fiveAns: " << fiveAns << "\n";
    ll totalAns = twoAns + fiveAns;
    if(L % 2 == 0) { // exclude lowerbound
        ll twoSub = binexp(2, (L + 1) / 2);
        ll fiveSub = binexp(5, (L + 1) / 2);
        totalAns -= twoSub;
        totalAns -= fiveSub;
    }
    if(R % 2 == 1) { // exclude upperbound
        ll twoSub = binexp(2, (R + 1) / 2);
        ll fiveSub = binexp(5, (R + 1) / 2);
        totalAns -= twoSub;
        totalAns -= fiveSub;
    }
    while(totalAns < 0) {
        totalAns += MOD;
    }   
    // cout << "totalAns: " << totalAns << "\n";
    cout << totalAns % MOD << "\n";
    return 0;
}