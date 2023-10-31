// https://open.kattis.com/problems/pollygone

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ld epsilon = 1E-10;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n; ld P; cin >> P;

    vector<vector<int>> dp(n + 1, vector<int>(1e4 + 1, 1e9));

    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        int e; cin >> e;
        ld p; cin >> p;
        int move = (int) ((p + epsilon) * 1e4);

        for(int j = 0; j <= 1e4; j++) {
            dp[i][j] = min(dp[i][j], dp[i-1][j]);

            if(j - move >= 0) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-move] + e);
            }

        }
    }

    int int_p = (int) ((P + epsilon) * 1e4);
    int ans = INT_MAX;
    for(int i = int_p; i <= 1e4; i++) {
        ans = min(ans, dp[n][i]);
    }

    cout << ans << '\n';

    return 0;
}