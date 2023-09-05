#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
int n;
int dp[11234][1123];
int a[1123];
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
   
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = 1123456;
        }
    }
    // dp[1][1] = a[1] + a[2];
    dp[2][1] = a[2];
    // dp[i][j] = min cost to get to i using j as last step
    for (int i = 2; i <= n-1; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i > j) {
                dp[i+1][j+1] = min(dp[i+1][j+1], dp[i][j] + a[i+1] + a[i-j]);
            }
            if (i + j + 1 <= n) {
                dp[i+j+1][j+1] = min(dp[i+j+1][j+1], dp[i][j] + a[i+j+1]);
            }
        }
    }
    int mn = 1123456;
    for (int j = 1; j <= n; ++j) {
        mn = min(mn, dp[n][j]);
        // cerr << "j : " << dp[n][j] << endl;
    }
    cout << mn << endl;
    return 0;
}
