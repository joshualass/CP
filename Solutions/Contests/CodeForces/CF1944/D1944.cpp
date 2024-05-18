#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;

/*
dp[i][j][k]
i - at current index i in the array
j - value at index i - 2
k - value at index i - 1

n^3 states --> need constant transitions



*/


void solve() {
    ll n, k; cin >> n >> k >> MOD;
    vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(k + 1, vector<ll>(k + 1)));
    for(ll i = 0; i <= k; i++) {
        dp[0][0][i] = 1;
    }

    for(ll i = 1; i < n; i++) {
        for(ll j = 0; j <= k; j++) {
            for(ll l = 0; l <= k; l++) {
                dp[i][l][max(0LL, l - j)] += dp[i-1][j][l];
                dp[i][l][max(0LL, l - j)] %= MOD;
            }
        }
        for(ll j = 0; j <= k; j++) {
            for(ll l = 0; l <= k; l++) {
                if(l != 0) {
                    dp[i][j][l] += dp[i][j][l-1];
                    if(dp[i][j][l] >= MOD) {
                        dp[i][j][l] %= MOD;
                    }
                }
            }
        }        
    }
    ll res = 0;
    for(ll i = 0; i <= k; i++) {
        for(int j = 0; j <= k; j++) {
            if(j <= i) {
                res += dp[n-1][i][j];
            }
        }
    }
    cout << res % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}