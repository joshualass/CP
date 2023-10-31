// https://open.kattis.com/problems/lostinthewoods

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<int>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<array<ld,2>> dp(n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 2; j++) {
            dp[i][j] = 0;
        }
    }

    dp[0][0] = 1;

    ld expected = 0;

    for(int i = 0; i < 1e4; i++) {

        int curr = i & 1;
        int next = curr ^ 1;

        for(int j = 0; j < n; j++) {
            dp[j][next] = 0;
        }

        for(int j = 0; j < n; j++) {
            ld add = dp[j][curr] / adj[j].size();

            for(auto x : adj[j]) {
                dp[x][next] += add;
            }
        }

        expected += (i + 1) * dp[n - 1][next];
        dp[n - 1][next] = 0;

    }

    cout << fixed << setprecision(10) << expected << '\n';



    return 0;
}