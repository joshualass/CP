#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int>(n));
    vector<vector<pair<int, int>>> loc(k);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) {
            cin >> a[i][j];
            a[i][j] --;
            loc[a[i][j]].push_back({i, j});
        }
    }
    bool is_valid = true;
    for(int i = 0; i < k; i++){
        if(loc[i].size() == 0) is_valid = false;
    }
    if(!is_valid) {
        cout << "-1\n";
        return 0;
    }
    vector<vector<int>> dp(k);
    for(int i = 0; i < k; i++) dp[i] = vector<int>(loc[i].size(), 1e9);
    dp[0] = vector<int>(loc[0].size(), 0);
    for(int i = 0; i < k - 1; i++){
        for(int cur = 0; cur < dp[i].size(); cur++){
            for(int next = 0; next < dp[i + 1].size(); next++){
                
                dp[i + 1][next] = min(dp[i + 1][next], dp[i][cur] + abs(loc[i][cur].first - loc[i + 1][next].first) + abs(loc[i][cur].second - loc[i + 1][next].second));
            }
        }
    }
    // vector<vector<int>> tmp(n, vector<int>(n));
    // for(int i = 0; i < k; i++){
    //     for(int j = 0; j < loc[i].size(); j++){
    //         tmp[loc[i][j].first][loc[i][j].second] = dp[i][j];
    //     }
    // }
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++) cout << tmp[i][j] << " ";
    //     cout << "\n";
    // }
    int ans = 1e9;
    for(int i = 0; i < dp[k - 1].size(); i++){
        ans = min(ans, dp[k - 1][i]);
    }
    cout << ans << "\n";

    return 0;
}
