#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll const MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<ll>> mat(n, vector<ll>(2));
    vector<vector<ll>> dp(n, vector<ll>(2));
    for(int i = 0; i < n; i++) {
        cin >> mat[i][0];
        cin >> mat[i][1];
        if(i == 0) {
            dp[i][0] = 1;
            dp[i][1] = 1;
        } else {
            if(mat[i][0] != mat[i-1][0]) {
                dp[i][0] += dp[i-1][0];
            }
            if(mat[i][0] != mat[i-1][1]) {
                dp[i][0] += dp[i-1][1];
            }
            if(mat[i][1] != mat[i-1][0]) {
                dp[i][1] += dp[i-1][0];
            }
            if(mat[i][1] != mat[i-1][1]) {
                dp[i][1] += dp[i-1][1];
            }
            dp[i][0] %= MOD;
            dp[i][1] %= MOD;
        }
    }
    cout << (dp[n-1][0] + dp[n-1][1]) % MOD;

    return 0;
}