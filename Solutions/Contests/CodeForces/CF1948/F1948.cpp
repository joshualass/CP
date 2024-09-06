#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    vector<int> pa(n + 1), pb(n + 1);

    for(int i = 1; i <= n; i++) {
        int num; cin >> num;
        pa[i] = pa[i-1] + num;
    }

    for(int i = 1; i <= n; i++) {
        int num; cin >> num;
        pb[i] = pb[i-1] + num;
    }

    int totalg = pa[n];
    int totals = pb[n];

    vector<ll> pc(totals + 1);
    pc[0] = 1;

    for(int i = 1; i <= totals; i++) {
        pc[i] = (pc[i - 1] + choose(totals,i)) % MOD;
    }

    ll poss = modInverse(binexp(2, totals), MOD);

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;

        int ag = pa[r] - pa[l - 1];
        int bg = totalg - ag;
        int as = pb[r] - pb[l - 1];
        int bs = totals - as;

        int needed = -(ag - bg - bs) + 1;

        // cout << "i : " << i << " needed : " << needed << '\n';

        if(needed <= totals) {
            cout << (pc[min(totals, totals - needed)] * poss) % MOD;
        } else {
            cout << "0";
        }
        cout << " \n"[i == q - 1];
    }

    return 0;
}