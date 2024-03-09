#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int m, s; cin >> m >> s;
    vector<pair<int,int>> coins(m);
    for(auto &x : coins) cin >> x.first >> x.second;
    vector<vector<int>> dp(s+1,vector<int>(s+1,1e9));
    dp[0][0] = 0;
    int ans = 1e9;
    for(int i = 0; i <= s; i++) {
        for(int j = 0; j <= s; j++) {
            for(int k = 0; k < m; k++) {
                if(i + coins[k].first <= s && j + coins[k].second <= s) {
                    dp[i+coins[k].first][j+coins[k].second] = min(dp[i+coins[k].first][j+coins[k].second], dp[i][j]+1);
                }
            }
            if(i * i + j * j == s * s) {
                ans = min(ans,dp[i][j]);
            }
        }
    }
    cout << (ans == 1e9 ? "not possible" : to_string(ans)) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}