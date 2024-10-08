#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

    ll n, k; cin >> n >> k;

    vector<vector<ll>> dp(n+1,vector<ll>(k));
    ll res = 0;
    dp[0][0] = 1;
    
    for(int i = 1; i <= n; i++) {
        for(int j = k; j > 0; j--) {
            //to get to current j, how many different p can we choose from
            ll free_p = k - j + 1;
            dp[i][j % k] = dp[i-1][j-1] * free_p % MOD;
            if(j == k) {
                res = (res + dp[i][0] * binexp(k,n-i)) % MOD;
            }
            if(j + 1 < k) {
                dp[i-1][j] = (dp[i-1][j] + dp[i-1][j+1]) % MOD;
            }
            if(j < k) {
                dp[i][j] = (dp[i][j] + dp[i-1][j]) % MOD;
            }

        }
    }

    cout << res << '\n';

    return 0;
}