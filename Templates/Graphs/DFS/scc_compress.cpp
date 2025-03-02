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