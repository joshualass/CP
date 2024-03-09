#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<string> v(n);
    for(auto &x: v) cin >> x;
    vector<vector<ll>> dp(n,vector<ll>(n));
    if(v[0][0] == '*') {
        cout << "0\n";
        return 0;
    }
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(v[i][j] == '*') continue;
            if(i != 0) {
                dp[i][j] += dp[i-1][j];
            }
            if(j != 0) {
                dp[i][j] += dp[i][j-1];
            }
            dp[i][j] %= MOD;
        }
    }
    cout << dp[n-1][n-1] << "\n";
    return 0;
}