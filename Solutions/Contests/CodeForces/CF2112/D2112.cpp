#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int p = -1;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 2) p = i;
    }

    if(p == -1) {
        cout << "NO\n";
        return;
    }

    vector<array<int,2>> res;

    auto dfs = [&](auto self, int i, int p, int push) -> void {
        for(int c : adj[i]) {
            if(c != p) {
                if(push) {
                    res.push_back({i, c});
                } else {
                    res.push_back({c, i});
                }
                self(self, c, i, push ^ 1);
            }
        }
    };

    int a = adj[p][0], b = adj[p][1];
    res.push_back({a, p});
    res.push_back({p, b});
    
    dfs(dfs, a, p, 1);
    dfs(dfs, b, p, 0);

    cout << "YES\n";
    for(auto x : res) {
        cout << x[0] + 1 << " " << x[1] + 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}