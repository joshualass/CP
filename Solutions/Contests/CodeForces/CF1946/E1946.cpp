#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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
    int n, m1, m2; cin >> n >> m1 >> m2;
    vector<ll> p(m1);
    vector<ll> s(m2);
    for(ll &x : p) cin >> x;
    for(ll &x : s) cin >> x;

    if(p.back() != s.front() || p.front() != 1 || s.back() != n) {
        cout << "0\n";
        return;
    }

    set<ll> sp(p.begin(), p.end());
    set<ll> ss(s.begin(), s.end());
    ll res = 1;

    for(ll i = 1; i < p.back(); i++) {
        if(sp.count(i) == 0) {
            res *= (i - 1);
            if(res >= MOD) {
                res %= MOD;
            }
        }
    }
    // cout << "rp : " << res << '\n';
    for(ll i = n; i > s.front(); i--) {
        if(ss.count(i) == 0) {
            res *= n - i;
            if(res >= MOD) {
                res %= MOD;
            }
        }
    }

    ll nck = choose(n - 1, p.back() - 1);
    // cout << "r : " << res << " nck : " << nck << '\n';
    cout << res * nck % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    factorial();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}