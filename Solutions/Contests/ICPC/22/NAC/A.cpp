#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k, m;
    cin >> n >> k >> m;
    vector<vector<pair<int, int>>> c(n);
    vector<int> l(n, -1);
    for(int i = 0; i < m; i++){
        int u, v, d;
        cin >> u >> v >> d;
        u --, v --;
        c[u].push_back({v, d});
        c[v].push_back({u, d});
        l[u] = max(l[u], d);
        l[v] = max(l[v], d);
    }
    vector<vector<bool>> dp(n, vector<bool>(k + 1, false));
    for(int i = 0; i < n; i++){
        if(l[i] == 1) dp[i][0] = true;
    }
    for(int i = 1; i <= k; i++){
        for(int j = 0; j < n; j++){
            if(l[j] > i + 1) continue;
            for(pair<int, int> x : c[j]) {
                int next = x.first;
                int d = x.second;
                if(d != i) continue;

                if(dp[next][i - 1]) dp[j][i] = true;
            }
        }
    }
    // for(int i = 0; i <= k; i++){
    //     for(int j = 0; j < n; j++) cout << dp[j][i] << " ";
    //     cout << "\n";
    // }
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        if(dp[i][k]) ans.push_back(i);
    }
    cout << ans.size() << "\n";
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size(); i++) cout << ans[i] + 1 << "\n";

    return 0;
}