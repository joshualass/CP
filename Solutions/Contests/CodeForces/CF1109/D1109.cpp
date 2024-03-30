#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const int N = 2e6;
ll factorials[N+1];
ll fibfactorials[N+1];
ll ff[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
    fibfactorials[0] = 1;
    fibfactorials[1] = 1;
    fibfactorials[2] = 1;
    ff[0] = 1;
    ff[1] = 1;
    ff[2] = 1;
    for(int i = 3; i <= n; i++) {
        fibfactorials[i] = fibfactorials[i-2] + fibfactorials[i-1];
        fibfactorials[i] %= MOD;
        ff[i] = ff[i-1] * fibfactorials[i] % MOD;
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

ll fibchoose(ll n, ll k) {
    // n--;
    // k--;
    if(k > n) return 1;
    cout << "fibchoose n : " << n << " k : " << k << " n1 : " << ff[n] << " d1 : " << ff[n-k] << " d2 : " << ff[k] << '\n';
    return modDivide(ff[n],ff[n-k] * ff[k] % MOD);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    factorial();
    ll n, m, a, b; cin >> n >> m >> a >> b;

    ll res = 0;
    for(ll i = 0; i < n - 1; i++) {
        ll mult = factorials[n-2];
        ll rooted = i + 1;
        ll free = n - rooted;
        ll fc = fibchoose(free + rooted, free);
        ll bars = i;
        ll stars = m - (i+1);
        ll ec = choose(stars + bars, bars);
        ll freeedges = n - 2 - i;
        ll ep = binexp(m,freeedges);
        cout << "mult : " << mult << '\n';
        cout << "rooted : " << rooted << '\n';
        cout << "free : " << free << '\n';
        cout << "fc : " << fc << '\n';
        cout << "bars : " << bars << '\n';
        cout << "stars : " << stars << '\n';
        cout << "ec : " << ec << '\n';
        cout << "ep : " << ep << '\n';
        ll add = mult * fc % MOD * ec % MOD * ep % MOD;
        cout << "add : " << add << '\n';
        res +=add;
        res %= MOD;
    }
    cout << res << '\n';

    return 0;
}