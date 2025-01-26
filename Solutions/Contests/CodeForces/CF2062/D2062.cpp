#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[0] >> x[1];
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> b(n);

    auto dfs0 = [&](auto self, int i, int p) -> void {
        ll mc = 0;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                mc = max(mc, b[c]);
            }
        }
        if(a[i][0] > mc) {
            b[i] = a[i][0];
        } else if(a[i][1] < mc) {
            b[i] = a[i][1];
        } else {
            b[i] = mc;
        }
    };

    dfs0(dfs0, 0, -1);
    vector<ll> dp(n);

    auto dfs = [&](auto self, int i, int p) -> void {
        ll res = 0;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                res += dp[c];
            }
        }
        if(p != -1 && b[i] > b[p]) {
            res += b[i] - b[p];
        }
        dp[i] = res;
    };

    dfs(dfs, 0, -1);
    cout << dp[0] + b[0] << '\n';

    // ll res = LLONG_MAX;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}