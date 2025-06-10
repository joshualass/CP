#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    vector<vector<array<int,2>>> par(n + 1, vector<array<int,2>>(m + 1));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(dp[i-1][j] >= dp[i][j]) {
                dp[i][j] = dp[i-1][j];
                par[i][j] = {i-1, j};
            }
            if(dp[i][j-1] >= dp[i][j]) {
                dp[i][j] = dp[i][j-1];
                par[i][j] = {i, j - 1};
            }
            if(a[i-1] == b[j-1] && dp[i-1][j-1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
                par[i][j] = {i-1,j-1};
            }
        }
    }

    int ca = n, cb = m;
    vector<int> res;
    while(ca && cb) {
        int na = par[ca][cb][0], nb = par[ca][cb][1];
        if(na < ca && nb < cb) {
            res.push_back(a[ca-1]);
        }
        ca = na;
        cb = nb;
    }

    cout << res.size() << '\n';
    reverse(res.begin(), res.end());
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " \n"[i == res.size() - 1];
    }

    return 0;
}
