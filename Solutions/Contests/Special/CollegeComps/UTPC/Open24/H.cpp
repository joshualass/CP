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
    ll n, q; cin >> n >> q;
    vector<ll> a(n+1);
    // for(ll &x : a) cin >> x;
    for(int i = 1; i<= n; i++) {
        cin >> a[i];
    }

    // vector<vector<ll>> mat(1000,vector<ll>(n));

    // for(ll i = 0; i < 1000; i++) {
    //     for(ll j = 0; j < n; j++) {
    //         if(j == 0) {
    //             mat[i][j] = a[j];
    //         } else {
    //             if(i == 0) {
    //                 mat[i][j] = mat[i][j-1] * a[j] % MOD;
    //             } else {
    //                 mat[i][j] = mat[i][j-1] * mat[i-1][j] % MOD;
    //             }
    //         }
    //     }
    // }   

    for(int i = 0; i < q; i++) {
        ll k, x; cin >> k >> x;
        ll res = a[x];
        for(int j = 1; j < x; j++) {
            ll power = choose(k + j - 1, j);
            res = res * binexp(a[x - j], power) % MOD;
        }
        cout << res << '\n';
        // cout << mat[k-1][x-1] << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    factorial();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}