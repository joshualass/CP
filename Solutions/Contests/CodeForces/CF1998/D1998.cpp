#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<vector<int>> adj2(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[v].push_back(u);
        adj2[u].push_back(v);
    }

    vector<int> dp(n,MOD);
    dp[0] = 0;
    vector<int> p(n + 1);

    for(int i = 0; i < n; i++) {
        if(i) {
            dp[i] = dp[i-1] + 1;
            for(int c : adj[i]) {
                dp[i] = min(dp[i], dp[c] + 1);
            }
        }

        int furthest = -1;
        for(int c : adj2[i]) {
            furthest = max(furthest, c);
        }

        int lo = i + 1;
        int hi = furthest - dp[i] - 1;

        if(hi >= lo) {
            p[lo]++;
            p[hi]--;
        }
    }

    int c = 0;
    for(int i = 0; i < n - 1; i++) {
        c += p[i];
        cout << (c ? 0 : 1);
    }
    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}