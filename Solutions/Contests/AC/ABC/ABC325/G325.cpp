#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int k; cin >> k;
    int n = s.size();
    
    vector dp(n + 1, vector<int>(n + 1, 1e9));

    for(int len = 0; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            dp[l][r] = len;
            for(int m = l + 1; m < r; m++) {
                dp[l][r] = min(dp[l][r], dp[l][m] + dp[m][r]);
            }
            if(s[l] == 'o') {
                for(int m = l + 1; m < r; m++) {
                    if(s[m] == 'f' && dp[l+1][m] == 0) {
                        dp[l][r] = min(dp[l][r], max(0, dp[m+1][r] - k));
                    }
                }
            }
        }
    }

    cout << dp[0][n] << '\n';

    return 0;
}
