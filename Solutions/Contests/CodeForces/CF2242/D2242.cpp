#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    string a, b; cin >> a >> b;

    
    int n = sz(a), m = sz(b);
    vector<int> sa(n + 1), sb(m + 1);
    for(int i = 0; i < n; i++) {
        sa[i+1] = (sa[i] + a[i] - '0') % 10;
    }

    for(int i = 0; i < m; i++) {
        sb[i+1] = (sb[i] + b[i] - '0') % 10;
    }

    if(sa[n] != sb[m]) {
        cout << "-1\n";
        return;
    }

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            if(sa[i] == sb[j]) {
                dp[i][j] = max(dp[i][j], 1 + dp[i-1][j-1]);
            }
        }
    }

    cout << dp[n][m] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}