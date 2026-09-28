#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }
    vector<int> vis(n);

    auto dfs = [&](auto self, int i) -> void {
        vis[i] = 1;
        for(int c : adj[i]) {
            if(vis[c] == 0) {
                self(self, c);
            }
        }
    };

    dfs(dfs, 0);

    cout << accumulate(vis.begin(), vis.end(), 0) << '\n';

    return 0;
}
