#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 3e5;
ll factorials[N+1];

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

ll gcdExtended(ll a, ll b, ll *x, ll *y);
 
ll modInverse(ll b, ll m = MOD) {
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

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> pc(n + 5);
    pc[0] = 1;
    for(ll i = 1; i < n + 5; i++) {
        pc[i] = pc[i-1] * (i + k - 1) % MOD * modInverse(i) % MOD;
    }
    // cout << "n : " << n << " k : " << k << '\n';
    // cout << "pc : " << pc << '\n';
    
    vector<ll> a(n+1);
    for(int i = 1; i <= n; i++) {
        ll num; cin >> num;
        a[i] = (a[i] + num) % MOD;
        ll depth = 1;
        int curr = i;
        while(1) {
            int next = curr + (1 << (__builtin_ctz(curr)));
            if(next > n) break;
            ll sub = pc[depth] * a[i] % MOD;
            // cout << "i : " << i << " next : " << next << " sub : " << sub << '\n';
            a[next] = (a[next] + MOD - sub) % MOD;
            depth++;
            curr = next;
        }
    }
    
    for(int i = 1; i <= n; i++) {
        cout << a[i] << " \n"[i == n];
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