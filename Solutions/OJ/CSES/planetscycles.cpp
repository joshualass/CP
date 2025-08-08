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

    int n; cin >> n;
    vector<vector<int>> adj(n), radj(n);
    vector<int> t(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        adj[i].push_back(x);
        t[i] = x;
        radj[x].push_back(i);
    }

    vector<vector<int>> sccs = kosarajus(adj);

    vector<int> res(n, -1);
    for(auto scc : sccs) {
        if(scc.size() == 1 && t[scc[0]] != scc[0]) continue;
        for(int x : scc) {
            res[x] = scc.size();
        }
        queue<array<int,2>> q;
        for(int x : scc) {
            for(int y : radj[x]) {
                if(res[y] == -1) {
                    q.push({y, ((int) scc.size()) + 1});
                }
            }
        }
        while(q.size()) {
            auto [x, d] = q.front();
            q.pop();
            res[x] = d;
            for(int y : radj[x]) q.push({y, d + 1});
        }
    }

    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

    return 0;
}
