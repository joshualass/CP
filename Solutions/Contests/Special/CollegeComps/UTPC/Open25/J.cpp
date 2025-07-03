#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    map<int,vector<array<int,2>>> edges;
    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        edges[c].push_back({a, b});
    }

    int ok = 1;

    vector<vector<int>> adj(n);
    vector<int> vis(n);
    vis[0] = 1;

    auto dfs = [&](auto self, int i) -> int {
        
        if(vis[i] == 0) {
            vis[i] = 2;

            int f = 0;
            for(int to : adj[i]) {
                if(self(self, to)) {
                    f = 1;
                }
            }

            // cout << "f : " << f << '\n';

            if(f) {
                vis[i] = 1;
            } else {
                ok = 0;
                return 0;
            }

        } else if(vis[i] == 1) {
            return 1;
        } 
    };

    for(auto [k, es] : edges) {
        for(auto edge : es) {
            adj[edge[0]].push_back(edge[1]);
        }

        for(auto edge : es) {
            if(vis[edge[0]] == 1) {
                // cout << "k : " << k << " call dfs to : " << edge[1] << '\n';
                dfs(dfs, edge[1]);
            }
        }
    }

    cout << (ok ? "YES" : "NO") << '\n';

    return 0;
}
