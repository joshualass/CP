#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    /*
    dp[i][j]
    i - prefix i starting with lowest value cards. 
    j - 1's needed
    */
    vector<vector<ll>> dp(m+1, vector<ll>(m+1));
    dp[0][0] = 1;

    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= m; j++) {

            if(j) {
                dp[i][j] += dp[i-1][j-1];
            }

            if(j != m) {
                dp[i][j] += dp[i-1][j+1];
            }

            if(dp[i][j] >= MOD) {
                dp[i][j] -= MOD;
            }

        }
    }

    // cout << "start ones needed\n";
    // for(int i = 0; i <= m; i++) {
    //     cout << "i : " << i << " dp : " << dp[m][i] << '\n';
    // }

    if(n == 1) {
        cout << dp[m][0] << '\n';
        return 0;
    }

    vector<vector<ll>> dpp(n-1, vector<ll>(m + 1));
    for(int i = 0; i <= m; i++) {
        dpp[0][i] = dp[m][i];
    }

    for(int i = 1; i < n - 1; i++) {
        for(int j = 0; j <= m; j++) {
            for(int k = 0; k <= j; k++) {
                dpp[i][j] += dpp[i-1][k] * dp[m][j - k];
                dpp[i][j] %= MOD;
            }
        }
    }

    // cout << "prop ones needed\n";
    // for(int i = 0; i <= m; i++) {
    //     cout << "i : " << i << " ways : " << dpp[n-2][i] << '\n';
    // }

    ll res = 0;

    for(int i = 0; i <= m; i++) {
        res += dp[m][i] * dpp[n-2][i];
        res %= MOD;
    }

    cout << res % MOD << '\n';

    return 0;
}