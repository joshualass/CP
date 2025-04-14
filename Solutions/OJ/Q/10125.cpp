#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<int> dx = {0, -1, 0, 1}, dy = {1, 0, -1, 0};

    vector<vector<array<int,4>>> dp(n, vector<array<int,4>>(n));

    auto dfs = [&](auto self, int x, int y, int f) -> int {
        // cout << "x : " << x << " y : " << y << " f : " << f << '\n';
        if(dp[x][y][f] == -1 || dp[x][y][f] == -2) {
            dp[x][y][f] = -1;
            return -1;
        }
        if(dp[x][y][f] > 0) return dp[x][y][f];

        dp[x][y][f] = -2;
        int succ = -1;

        for(int i = 3; i < 7; i++) {
            int ti = (f + i) % 4;
            int nx = x + dx[ti];
            int ny = y + dy[ti];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if(a[nx][ny] == '.') {
                    succ = self(self, nx, ny, ti);
                    break;
                }
            } else {
                succ = 0;
                break;
            }
        }
        // cout << "succ : " << succ << '\n';
        if(succ == -1) {
            dp[x][y][f] = -1;
        } else {
            dp[x][y][f] = succ + 1;
        }
        return dp[x][y][f];
    };

    // dfs(dfs, 1, 9, 0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < 4; k++) {
                dfs(dfs, i, j, k);
            }
        }
    }

    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < n; j++) {
    //         cout << dp[i][j][0] << " \n"[j == n - 1];
    //     }
    // }

    for(int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        char c; cin >> c;
        int f;
        switch(c) {
            case 'R' : f = 0; break;
            case 'U' : f = 1; break;
            case 'L' : f = 2; break;
            case 'D' : f = 3; break;
        }
        x--; y--;
        cout << dp[x][y][f] << '\n';
    }


    return 0;
}
