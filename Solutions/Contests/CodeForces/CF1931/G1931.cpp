#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 2e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N, ll MOD = MOD) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
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

ll inverse(ll b) {
    return binexp(b,MOD-2);
}

//returns a / b using modular inverse. this implementation uses fermat's little theorem
ll modDivide(ll a, ll b) {
    return binexp(b,MOD-2) * a % MOD;
}

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

ll generate(ll as, ll bs, ll a , ll b) {
    return choose(a + as - 1, a) * choose(b + bs - 1, b) % MOD;
}

void solve() {
    ll a, b, c, d; cin >> a >> b >> c >> d;
    ll ans = 0;
    if(abs(a-b) == 1) {
        ans += generate((a+b+1)/2,(a+b+1)/2,c,d);
    } else if(a == b) {
        ans += generate(a+1,a,c,d);
        ans += generate(a,a+1,c,d);
        if(a == 0) {
            ans += (c == 0 || d == 0);
        }
    }
    cout << ans % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    factorial();

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}