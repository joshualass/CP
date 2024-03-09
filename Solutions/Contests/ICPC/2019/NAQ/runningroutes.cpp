#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> mat(n,vector<int>(n));

    for(auto &x : mat) {
        for(int &y : x) cin >> y;
    }
    vector<vector<int>> dp(n,vector<int>(n));

    for(int diff = 1; diff < n; diff++) {
        for(int lo = 0; lo + diff < n; lo++) {
            int hi = lo + diff;
            if(diff != 1) {
                dp[lo][hi] = dp[lo+1][hi-1];
            }
            dp[lo][hi] += mat[lo][hi];
            for(int lstart = lo + 2; lstart < hi; lstart++) {
                dp[lo][hi] = max(dp[lo][hi], dp[lo][lstart-1] + dp[lstart][hi]);
            }
            dp[lo][hi] = max({dp[lo][hi-1], dp[lo+1][hi],dp[lo][hi]});
        }
    }

    cout << dp[0][n-1] << '\n';

    return 0;
}