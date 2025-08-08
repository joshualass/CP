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

pair<vector<vector<int>>, vector<int>> compress_SCC(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> a(n);

    vector<vector<int>> sccs = kosarajus(adj);

    vector<int> scc_id(n);
    for(int i = 0; i < sccs.size(); i++) {
        for(int x : sccs[i]) {
            scc_id[x] = i;
        }
    }

    vector<vector<int>> upd_adj(sccs.size());
    set<array<int,2>> edges;
    for(int i = 0; i < n; i++) {
        for(int to : adj[i]) {
            int i_id = scc_id[i], to_id = scc_id[to];
            if(i_id != to_id && edges.count({i_id,to_id}) == 0) {
                upd_adj[i_id].push_back(to_id);
                edges.insert({i_id,to_id});
            }
        }
    }
    return {upd_adj, scc_id};
}

//minimal side effect topological sort
void _topological(int i, vector<vector<int>> &adj, vector<bool> &visited, vector<int> &ans) {
    // cout << "top sort: " << i << '\n';
    visited[i] = true;
    for(auto x : adj[i]) {
        if(!visited[x]) {
            _topological(x,adj,visited,ans);
        }
    }
    ans.push_back(i);
}

vector<int> topological_sort(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<bool> visited(n);
    vector<int> ans;

    for(int i = 0; i < n; i++) {
        if(!visited[i]) {
            _topological(i, adj, visited, ans);
        }
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
    }    

    auto [scc_adj, scc_id] = compress_SCC(adj);

    vector<ll> b(scc_id.size());
    for(int i = 0; i < n; i++) {
        b[scc_id[i]] += a[i];
    }

    vector<int> top = topological_sort(scc_adj);
    vector<ll> add(scc_id.size());

    for(int i = 0; i < top.size(); i++) {
        int x = top[i];
        b[x] += add[x];
        for(int c : scc_adj[x]) {
            add[c] = max(add[c], b[x]);
        }
    }

    cout << *max_element(b.begin(), b.end()) << '\n';

    return 0;
}
