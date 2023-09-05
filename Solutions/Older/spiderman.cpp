#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T; cin >> T;
    while(T-->0) {
        int distances; cin >> distances;
        vector<vector<pair<int,vector<bool>>>> dp(distances + 1, vector<pair<int,vector<bool>>>(501, pair<int,vector<bool>>(INT_MAX,0)));
        dp[0][0].first = 0;
        for(int r = 0; r < distances; r++) {
            int d; cin >> d;
            for(int c = 0; c < 501; c++) {
                if(dp[r][c].first != INT_MAX) {
                    // cout << "r: " << r << " c: " << c << " d: " << d << '\n';
                    if(c + d <= 500) {
                        if(dp[r+1][c+d].first > max(dp[r][c].first, c+d)) {
                            vector<bool> temp = dp[r][c].second;
                            temp.push_back(true);
                            dp[r+1][c+d] = {max(dp[r][c].first,c+d), temp};
                        }
                    }
                    if(c - d >= 0) {
                        // cout << "huh: " << dp[r+1][c - d].first << " ??? " << dp[r][c].first << '\n';
                        if(dp[r+1][c - d].first > dp[r][c].first) {
                            // cout << "current r & c: " << r << " " << c << " pushing to: " << r + 1 << " " << c - d << " max value: " << dp[r][c].first << '\n';
                            vector<bool> temp = dp[r][c].second;
                            temp.push_back(false);
                            dp[r+1][c-d] = {dp[r][c].first, temp};                            
                        }
                    }
                }
            }
        }
        if(dp[distances][0].first != INT_MAX) {
            for(bool x : dp[distances][0].second) {
                cout << ((bool)x ? 'U' : 'D');
            }
            cout << '\n';
        } else {
            cout << "IMPOSSIBLE\n";
        }
    }

    return 0;
}