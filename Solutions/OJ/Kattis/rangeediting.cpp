#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
failed for a while. coordinate compressed incorrectly X_x
dp[l][r] => minimum # of operations to paint the interval [l, r], having the outermost operation be of color a[l], which can be extended to the left. 
state took a little bit of time to come up with, and this solution is very clean. 
*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    a.insert(a.begin(), 0);
    n++;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
    for(int len = 0; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            if(len == 0) {
                dp[l][r] = 0;
            } else {
                dp[l][r] = 1 + dp[l+1][r];
                for(int i = l + 1; i < r; i++) {
                    if(a[i] == a[l]) {
                        dp[l][r] = min(dp[l][r], dp[l+1][i] + dp[i][r]);
                    }
                }
            }
        }
    }

    cout << dp[0][n] - 1 << '\n';

    return 0;
}
