#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<array<ll,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll res = LLONG_MAX;

    vector<int> vis(n);

    auto dfs = [&](auto self, int i, ll cx) -> void {
        if(vis[i]) return;
        if(i == n - 1) {
            res = min(res, cx);
            return;
        }
        vis[i] = 1;
        for(auto [to, w] : adj[i]) self(self, to, cx ^ w);
        vis[i] = 0;
    };

    dfs(dfs, 0, 0);

    cout << res << '\n';

    return 0;
}
