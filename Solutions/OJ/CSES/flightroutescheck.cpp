#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void kdfs(int i, vector<vector<int>> &adj, vector<int> &order, vector<int> &vis) {
    vis[i] = 1;
    for(int x : adj[i]) {
        if(vis[x] == 0) {
            kdfs(x,adj,order,vis);
        }
    }
    order.push_back(i);
}

void sdfs(int i, vector<vector<int>> &adj, vector<int> &vis, vector<vector<int>> &sccs) {
    vis[i] = 2;
    sccs.back().push_back(i);
    for(int x : adj[i]) {
        if(vis[x] == 1) {
            sdfs(x,adj,vis,sccs);
        }
    }
}

vector<vector<int>> kosarajus(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> tp(n);
    for(int i = 0; i < n; i++) {
        for(int x : adj[i]) {
            tp[x].push_back(i);
        }
    }
    
    vector<int> order(n);
    vector<int> vis(n);
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            kdfs(i,adj,order,vis);
        }
    }
    reverse(order.begin(), order.end());
    vector<vector<int>> sccs;
    for(int i = 0; i < n; i++) {
        if(vis[order[i]] == 1) {
            sccs.push_back({});
            sdfs(order[i],tp,vis,sccs);
        }
    }
    return sccs;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vector<vector<int>> sccs = kosarajus(adj);
    if(sccs.size() == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        int a = sccs[0][0], b = sccs[1][0];
        vector<int> vis(n);
        auto dfs = [&](auto self, int i) -> void {
            if(vis[i]) return;
            vis[i] = 1;
            for(int c : adj[i]) self(self, c);
        };
        dfs(dfs, a);
        if(vis[b] == 0) {
            cout << a + 1 << " " << b + 1 << '\n';
        } else {
            cout << b + 1 << " " << a + 1 << '\n';
        }
    }

    return 0;
}
