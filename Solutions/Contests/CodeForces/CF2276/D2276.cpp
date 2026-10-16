#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++) {
        if(adj[i].empty()) {
            cout << "Brain Melt\n";
            return;
        }
    }

    vector<int> vis(n);
    auto dfs = [&](auto self, int i) -> void {
        if(vis[i]) return;
        vis[i] = 1;
        for(int c : adj[i]) self(self, c);
    };

    dfs(dfs, 0);
    int oc = 0;
    for(int i = 0; i < n; i++) {
        if(sz(adj[i]) > 1) oc++;
    }

    cout << (accumulate(vis.begin(), vis.end(), 0) == n && oc <= 1 ? "2" : "Many") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}