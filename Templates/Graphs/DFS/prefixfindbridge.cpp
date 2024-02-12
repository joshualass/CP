void spanning_dfs(int i, vector<map<int,int>> &adj, vector<bool> &visited, set<pair<int,int>> &spanning_edges) {
    visited[i] = 1;
    for(pair<int,int> p : adj[i]) {
        if(visited[p.first] == 0) {
            spanning_edges.insert({i,p.first});
            spanning_dfs(p.first, adj, visited, spanning_edges);
        }
    }
}

void bridge_dfs(int i, int p, vector<map<int,int>> &adj, vector<bool> &visited, set<pair<int,int>> &spanning_edges, set<pair<int,int>> &bridges, vector<int> &dp) {
    visited[i] = 1;
    for(pair<int,int> edge : adj[i]) {
        if(visited[edge.first]) {
            dp[i]++;
        } else {
            dp[i]--;
        }
    }
    for(pair<int,int> edge : adj[i]) {
        if(spanning_edges.count({i,edge.first})) {
            bridge_dfs(edge.first, i, adj, visited, spanning_edges, bridges, dp);
            dp[i] += dp[edge.first];
        }
    }
    if(dp[i] == 1) bridges.insert({i,p});
}

set<pair<int,int>> find_bridges(vector<map<int,int>> &adj) {
    int n = adj.size();
    set<pair<int,int>> spanning_edges;
    vector<bool> visited(n);
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            spanning_dfs(i, adj, visited, spanning_edges);
        }
    }

    visited.assign(n,0);
    set<pair<int,int>> bridges;
    vector<int> prefixes(n);
    // cout << "spanning edges : " << spanning_edges << '\n';
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            bridge_dfs(i, -1, adj, visited, spanning_edges, bridges, prefixes);
        }
    }
    return bridges;
}