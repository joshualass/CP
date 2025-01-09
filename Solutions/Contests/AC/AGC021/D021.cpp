#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[301][301][301];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s; cin >> s;
    int k; cin >> k;
    int n = s.size();

    int res = 0;

    for(int length = n; length >= 0; length--) {
        for(int l = 0; l + length <= n; l++) {
            int r = l + length;
            for(int j = 0; j <= k; j++) {
                res = max(res, dp[l][r][j]);
                if(length == 0) continue;
                //move left pointer
                dp[l+1][r][j] = max(dp[l+1][r][j], dp[l][r][j]);
                //move right pointer
                dp[l][r-1][j] = max(dp[l][r-1][j], dp[l][r][j]);
                //same value at ends, add 2
                if(length >= 2 && s[l] == s[r-1]) {
                    dp[l+1][r-1][j] = max(dp[l+1][r-1][j], dp[l][r][j] + 2);
                }
                //not the same value at ends, do an operation to increase LCS by 2
                if(length >= 2 && s[l] != s[r-1] && j + 1 <= k) {
                    dp[l+1][r-1][j + 1] = max(dp[l+1][r-1][j+1], dp[l][r][j] + 2);
                }
                //can sneak in a final character in the middle
                if(length == 1) {
                    dp[l+1][r][j] = max(dp[l+1][r][j], dp[l][r][j] + 1);
                }
            }
        }
    }

    cout << res << '\n';

    return 0;
}