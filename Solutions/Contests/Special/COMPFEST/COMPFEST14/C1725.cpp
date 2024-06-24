#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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


signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    factorial();

    ll n, m; cin >> n >> m;
    set<ll> pos;
    ll totallength = 0;
    for(int i = 0; i < n; i++) {
        ll length; cin >> length;
        pos.insert(totallength);
        totallength += length;
    }

    ll numpairs = 0;
    if(totallength % 2 == 0) {
        for(ll x : pos) {
            numpairs += pos.count(x + totallength/2);   
        }
    }

    ll free = n - numpairs * 2;
    ll res = 0;
    // cout << "pairs : " << numpairs << " free : " << free << '\n';

    //y is number of diameters with matching colors
    for(ll y = 0; y <= min(numpairs,m); y++) {
        ll remainingcolors = m - y;
        ll remainingdiameters = numpairs - y;
        ll choosediameters = choose(numpairs, y);
        ll choosecolors = choose(m,y);
        ll assigncolors = factorials[y];
        ll assignfrees = binexp(remainingcolors, free);
        ll assignfreediameters = binexp(remainingcolors * (remainingcolors - 1) % MOD, remainingdiameters);
        ll add = choosediameters * choosecolors % MOD * assigncolors % MOD * assignfrees % MOD * assignfreediameters % MOD;
        // cout << "y : " << y << " cd : " << choosediameters << " cc : " << choosecolors << " ac : " << assigncolors << " free : " << assignfrees << " afd : " << assignfreediameters << " add : " << add << '\n';
        res += add;
    }

    cout << res % MOD << '\n';

    return 0;
}