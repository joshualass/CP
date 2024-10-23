#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
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

vector<ll> fact(1,1);
vector<ll> inv_fact(1,1);

ll choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    while(fact.size() < n + 1) {
        fact.push_back(fact.back() * fact.size() % MOD);
        inv_fact.push_back(modInverse(fact.back(), MOD));
    }

    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}

void solve() {
    
    int n; cin >> n;
    vector<ll> cnts(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        cnts[num]++;
    }

    vector<ll> dp(n+1,1), dpp(n+1,1);

    ll res = 0;
    ll cumsum = 0;

    for(int i = 0; i < n; i++) {
        vector<ll> dpnext(cnts[i] + 1), dpnextp(cnts[i] + 1);
        cumsum += cnts[i];
        ll c = 0;
        // for(int j = min((int) cnts[i], (int) dp.size() - 1); j >= 0; j--) {
        for(int j = cnts[i]; j >= 0; j--) {
            if(i == 0) {
                c = choose(cnts[i],j);
            } else {
                c = (c + choose(cnts[i], j)) % MOD;
            }
            if(j <= min((int) cnts[i], (int) dp.size() - 1)) {
                dpnext[j] = (MOD + (dp[j] * c) + (dpp[j] * choose(cnts[i],j)) - (dp[j] * choose(cnts[i],j))) % MOD;
                res = (res + dpnext[j] * j % MOD * binexp(2,n-cumsum)) % MOD;
                // cout << "i : " << i << " j : " << j << " add : " << dpnext[j] * j % MOD * binexp(2,n-cumsum) << '\n';
                dpnextp[j] = dpnext[j];
                if(j < min((int) cnts[i], (int) dp.size() - 1)) {
                    dpnextp[j] = (dpnextp[j] + dpnextp[j+1]) % MOD;
                }
            }
        }
        dp = dpnext;
        dpp = dpnextp;

        // cout << "i : " << i << " dp : " << dp << '\n';
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}