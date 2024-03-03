#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 999999893;

ll binexp(ll base, ll power) {
    if(power < 0) return 0;
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

void polymult(ll &a, ll &b, ll c, ll d) {
    ll ac = a * c;
    ll cbad = (c * b + a * d);
    ll bd = 2 * b * d;
    a = (ac + bd) % MOD;
    b = cbad % MOD;
}

void solve() {
    ll n; cin >> n;
    //get mountain in form A + B
    ll ma = binexp(2,n/2+1) - 1;
    ll mb = binexp(2,(n+1)/2) - 1;
    //get valley in form A + B
    ll va = binexp(2,n/2+1) - 1;
    ll vb = binexp(2,(n+1)/2);
    //get discriminant of valley (denominator)
    ll vda = va;
    ll vdb = (-vb + MOD) % MOD;
    //multiply both sides by discriminant
    polymult(ma,mb,vda,vdb);
    polymult(va,vb,vda,vdb);
    //print mod inverse 
    cout << mb * modInverse(va,MOD) % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}