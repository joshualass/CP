#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    string s; cin >> s;
    vector<vector<bool>> vis(5, vector<bool>(5));

    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};
    vector<char> b = {'D', 'U', 'R', 'L'};
    int res = 0;
    int c = 0;
    auto dfs = [&](auto self, int i, int j, int len) -> void {
        c++;
        if(i == 4) {
            for(int k = j + 1; k < 5; k++) {
                if(vis[i][k] == 0) return;
            }
        }
        if(j == 4) {
            for(int k = i - 1; k >= 0; k--) {
                if(vis[k][j] == 0) return;
            }
        }
        
        if(len == 24) {
            if(i == 2 && j == 0) res++;
            return;
        }
        for(int k = 0; k < 4; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if(ni >= 0 && ni < 5 && nj >= 0 && nj < 5 && vis[ni][nj] == 0 && (s[len] == b[k] || s[len] == '?')) {
                vis[ni][nj] = 1;
                self(self, ni, nj, len + 1);
                vis[ni][nj] = 0;
            }
        }
    };

    dfs(dfs, 0, 0, 0);

    cout << res << '\n';

    cout << "c : " << c << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// int main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n; cin >> n;
//     vector<string> v(n);
//     for(auto &x: v) cin >> x;
//     vector<vector<ll>> dp(n,vector<ll>(n));
//     if(v[0][0] == '*') {
//         cout << "0\n";
//         return 0;
//     }
//     dp[0][0] = 1;
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < n; j++) {
//             if(v[i][j] == '*') continue;
//             if(i != 0) {
//                 dp[i][j] += dp[i-1][j];
//             }
//             if(j != 0) {
//                 dp[i][j] += dp[i][j-1];
//             }
//             dp[i][j] %= MOD;
//         }
//     }
//     cout << dp[n-1][n-1] << "\n";
//     return 0;
// }