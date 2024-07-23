#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//can be optimized using pollard's rho and inclusion/exclusion

//let's try optimization with SOS

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    ll shijak = m;
    vector<ll> factors;
    for(ll i = 2; i * i <= m; i++) {
        bool first = 1;
        while(m % i == 0) {
            if(first) {
                factors.push_back(i);
                first = 0;
            } else {
                factors.back() *= i;
            }
            m /= i;
        }
    }
    if(m != 1) {
        factors.push_back(m);
    }

    vector<int> dp(1 << factors.size());
    vector<int> b(1 << factors.size());

    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        if(shijak % a == 0) {
            int cbm = 0;
            for(int j = 0; j < factors.size(); j++) {
                if(a % factors[j] == 0) {
                    cbm += 1 << j;
                }
            }
            b[cbm]++;
        }
    }

    for(int i = 0; i < 1 << factors.size(); i++) {
        dp[i] = b[i];
    }

    //sum over subsets
    for(int i = 0; i < factors.size(); i++) {
        for(int bm = 0; bm < 1 << factors.size(); bm++) {
            if(bm & (1 << i)) {
                dp[bm] += dp[bm ^ (1 << i)];
            }
        }
    }

    ll res = 0;
    for(int bm = 0; bm < 1 << factors.size(); bm++) {
        if((factors.size() - __builtin_popcount(bm)) & 1) {
            res -= binexp(2, dp[bm]);
        } else {
            res += binexp(2, dp[bm]);
        }
    }

    res = (res + MOD * MOD) % MOD;

    if(shijak == 1) {
        cout << (res - 1 + MOD) % MOD << '\n';
    } else {
        cout << res << '\n';
    }

    return 0;
}