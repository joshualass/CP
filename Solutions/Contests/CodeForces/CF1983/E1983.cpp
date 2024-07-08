#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//guess some pattern GG
const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m) {
    ll x, y;
    ll g = gcdExtended(b, m, &x, &y);
 
    if (g != 1) return -1;
 
    return (x % m + m) % m;
}
  // Function to compute a/b under modulo m
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

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}


void solve() {
    ll n, k; cin >> n >> k;

    ll ss = 0, os = 0;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        if(i < k) {
            ss += num;
        } else {
            os += num;
        }
    }

    ll sc = k, oc = n - k;

    ll a = 0;
    ll b = 0;

    ss %= MOD;
    os %= MOD;

    if(sc) {
        ll specialaverage = ss * modInverse(sc,MOD) % MOD;
        ll magic = modInverse(n - k + 1, MOD) % MOD;

        // a += specialaverage * (k * ((n - k + 1 + 1) / 2)) % MOD * magic % MOD;
        // b += specialaverage * (k * ((n - k + 1) / 2)) % MOD * magic % MOD;
        a += specialaverage * k % MOD * ((n - k + 1LL + 1LL) / 2LL) % MOD * magic % MOD;
        b += specialaverage * k % MOD * ((n - k + 1LL) / 2LL) % MOD * magic % MOD;
    }

    // cout << "a : " << a % MOD << '\n';
    // cout << "b : " << b % MOD << '\n';

    if(oc) {
        a += os * ((oc + 1LL) / 2LL) % MOD * modInverse(oc,MOD);
        b += os * (oc / 2LL) % MOD * modInverse(oc,MOD);
    }

    cout << a % MOD << " " << b % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}