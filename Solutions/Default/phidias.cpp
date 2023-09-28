// https://dmoj.ca/problem/ioi04p4
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[601][601];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int w, h; cin >> w >> h;
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(auto &x: v) cin >> x.first >> x.second;
    for(int i = 0; i <= 600; i++) {
        dp[i][0] = 0;
        dp[0][i] = 0;
    }

    for(int i = 1; i <= w; i++) {
        for(int j = 1; j <= h; j++) {
            if(j == 1) {
                dp[i][j] = dp[i-1][h];
            } else {
                dp[i][j] = dp[i][j-1];
            }
            for(int s = 0; s < n; s++) {
                pair<int,int> p = v[s];
                if(i >= p.first && j >= p.second) {
                    dp[i][j] = min(dp[i][j], dp)
                }
            }
            // dp[i][j] = min(dp[i-1][j] + j,dp[i][j-1] + i);
            // for(int s = 0; s < n; s++) {
            //     pair<int,int> p = v[s];
            //     if(i >= p.first && j >= p.second) {
            //         if(dp[i-p.first][j] + dp[i][j-p.second] - dp[i-p.first][i-p.second] < 0) {
            //             cout << dp[i-p.first][j] << " " << dp[i][j-p.second] << " " << dp[i-p.first][i-p.second] << "\n";
            //         }
            //         dp[i][j] = min(dp[i][j], dp[i-p.first][j] + dp[i][j-p.second] - dp[i-p.first][i-p.second]);
            //     }
            // }
        }
    }
    for(int i = 0; i <= 21; i++) {
        for(int j = 0; j <= 11; j++) {
            cout << dp[i][j] <<  ' ';
        }
        cout << "\n";
    }
    cout << dp[w][h] << "\n";

    return 0;
}