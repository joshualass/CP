#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
very important that the cells visited are distinct, else we will have infinite cycles
*/

void solve() {
    
    int n, m, x, y; cin >> n >> m >> x >> y;
    x--, y--;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> res;
    vector<int> vis(n);
    int cur;

    auto append = [&](int idx) -> void {
        res.push_back(idx);
        vis[idx] = 1;
        cur =idx;
    };

    append(x);

    while(cur != y) {
        vector<int> vis2 = vis;
        auto dfs = [&](auto self, int idx) -> void {
            vis2[idx] = 1;
            for(int c : adj[idx]) if(vis2[c] == 0) self(self, c);
        };
        dfs(dfs, y);
        int nearest = n;
        for(int c : adj[cur]) {
            if(vis[c] == 0 && vis2[c]) nearest = min(nearest, c);
        }
        append(nearest);
    }

    for(int i = 0; i < res.size(); i++) {
        cout << res[i] + 1 << " \n"[i == res.size() - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}