#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, k, v; cin >> n >> k >> v;
    v--;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }    

    vector<int> par(n), depth(n);
    vector<vector<int>> at_depth(n);
    
    auto dfs = [&](auto self, int i, int p, int d) -> void {
        par[i] = p;
        depth[i] = d;
        at_depth[d].push_back(i);
        for(int c : adj[i]) {
            if(c != p) self(self, c, i, d + 1);
        }
    };

    dfs(dfs, v, -1, 0);
    vector<vector<int>> cc(n);

    auto get_dist = [&](int i) -> int {
        sort(cc[i].begin(), cc[i].end());
        if(sz(cc[i]) >= 2 && cc[i][0] + cc[i][1] <= k + 1) {
            return 0;
        }
        return cc[i][0];
    };

    for(int d = n - 1; d > 0; d--) {
        // cout << "d : " << d << endl;
        for(int i : at_depth[d]) {
            int dist;
            if(adj[i].size() == 1) {
                dist = 0;
            } else {
                dist = get_dist(i);
            }
            cc[par[i]].push_back(dist + 1);
        }
    }

    cout << (get_dist(v) == 0 ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}