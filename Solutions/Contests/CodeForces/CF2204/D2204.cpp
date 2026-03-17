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

    vector<int> vis(n);
    auto dfs = [&](auto self, int i, int col, int &ok, int &red, int &blue) -> void {
        if(vis[i]) {
            if(vis[i] != col) ok = 0;
            return;
        }
        vis[i] = col;
        if(col == 1) red++;
        if(col == 2) blue++;
        for(int to : adj[i]) self(self, to, 3 - col, ok, red, blue);
    };

    int res = 0;

    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            int ok = 1, red = 0, blue = 0;
            dfs(dfs, i, 1, ok, red, blue);
            if(ok) res += max(red, blue);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}