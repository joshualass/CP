#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[5001][5001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x; cin >> n >> x;
    array<vector<array<int,2>>, 3> b;
    for(int i = 0; i < n; i++) {
        int v, a, c; cin >> v >> a >> c;
        b[v-1].push_back({a,c});
    }

    auto poss = [&](int m) -> bool {
        int ok = 1, tc = 0;

        for(int v = 0; v < 3; v++) {
            for(int i = 0; i <= 5000; i++) for(int j = 0; j <= 5000; j++) dp[i][j] = -1;

            dp[0][0] = 0;
            int min_cal = INT_MAX;
            for(int i = 1; i <= b[v].size(); i++) {
                for(int j = 0; j <= x; j++) {
                    dp[i][j] = max(dp[i][j], dp[i-1][j]);
                    if(j >= b[v][i-1][1]) {
                        dp[i][j] = max(dp[i][j], dp[i-1][j - b[v][i-1][1]] + b[v][i-1][0]);
                    }
                    if(dp[i][j] >= m) min_cal = min(min_cal, j);
                }
            }
            if(min_cal == INT_MAX) {
                ok = 0;
            } else {
                tc += min_cal;
            }
        }

        return ok && tc <= x;

    };

    int l = 0, r = 200000 * 5000;
    while(l != r) {
        int m = (l + r + 1) / 2;
        if(poss(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << l << '\n';

    return 0;
}