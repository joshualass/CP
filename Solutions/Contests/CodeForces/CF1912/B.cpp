#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int N = 1e6;
ll factorials[N+1];

//finds all factorials 0-N iteratively
void factorial(int n = N) {
    factorials[0] = 1;
    for(int i = 1; i <= n; i++) {
        factorials[i] = factorials[i-1] * i % MOD;
    }
}

//TODO replace with template that supports all modular operations
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

//returns a / b using modular inverse. this implementation uses fermat's little theorem
ll modDivide(ll a, ll b) {
    return binexp(b,MOD-2) * a % MOD;
}

ll choose(ll n, ll k) {
    if(k > n) return 0;
    return modDivide(factorials[n],factorials[n-k] * factorials[k] % MOD);
}

ll compute(ll num_middles, ll spareseats) {
    ll ans = 0;
    for(ll num_twos = 0; num_twos * 2 <= spareseats; num_twos++) {
        assert(num_twos <= num_middles);
        ll num_ones = spareseats - num_twos * 2;
        if(num_twos + num_ones > num_middles) {
            continue;
        }

        ll num_zeroes = num_middles - num_ones - num_twos;
        ans += choose(num_middles, num_twos) * choose(num_middles - num_twos, num_ones);
        ans %= MOD;
    }
    return ans;
}

void solve() {
    
    ll n, k; cin >> n >> k;

    ll greedy_fill = n / (k * 2);
    ll remainder = n - greedy_fill * k * 2;

    ll mincost = greedy_fill * (greedy_fill - 1) * k + remainder * (greedy_fill);

    // cout << "greedy fill : " << greedy_fill << " remainder : " << remainder << '\n';

    cout << mincost << ' ';
    if(n < k * 2) {
        //edge case
        ll remainder = n - (k + 1);
        ll num_middles = k - 1;
        ll ans = choose(num_middles, remainder);
        cout << ans << '\n';
    } else {
        ll ans = 0;
        ans += compute(k - 1, remainder);
        if(remainder > 0) {
            ans += compute(k - 1, remainder - 1) * 2;
        }
        if(remainder > 1) {
            ans += compute(k - 1, remainder - 2);
        }
        cout << ans % MOD << '\n';
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