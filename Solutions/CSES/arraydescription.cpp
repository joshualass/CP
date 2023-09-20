#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    vector<vector<ll>> dp(n+1,vector<ll>(m+1));
    for(int i = 0; i <= m; i+=3) {
        dp[0][i] = 1;
    }
    for(int i = 1; i <=n ; i++) {
        for(int j = 1; j <= m; j++) {
            if(i == 1) {
                if(v[i-1] == 0 || v[i-1] == j) {
                    dp[i][j] = 1;
                }
            } else if(v[i-1] == 0 || v[i-1] == j) {
                dp[i][j] += dp[i-1][j];
                if(j != 1)dp[i][j] += dp[i-1][j-1];
                if(j != m) dp[i][j] += dp[i-1][j+1];
                dp[i][j] %= MOD;
            } 
        }
    }
    if(v.back() == 0) {
        ll sum = 0;
        for(auto x : dp[n]) {
            sum += x;
        }
        cout << sum %MOD << "\n";
    } else {
        cout << dp[n][v.back()] % MOD<< "\n";
    }
    return 0;
}