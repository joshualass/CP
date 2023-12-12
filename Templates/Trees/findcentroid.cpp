void calc_subtree_size(int i, int p, int edge_idx, vector<vector<int>> &adj, vector<vector<int>> &subsizes) {
    int size = 1;
    for(int j = 0; j < adj[i].size(); j++) {
        if(adj[i][j] != p) {
            if(subsizes[i][j] == -1) {
                // calc_subtree_size(adj[i][j].first, i, j, adj);
                calc_subtree_size(adj[i][j], i, j, adj, subsizes);
            }
            size += subsizes[i][j];
        }
    }
    // adj[p][edge_idx].second = size;
    subsizes[p][edge_idx] = size;
}

//pass in adj. list, returns centroids :P
vector<int> find_centroids(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> subsizes(n);
    //build subsizes
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < adj[i].size(); j++) {
            subsizes[i].push_back(-1);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < subsizes[i].size(); j++) {
            if(subsizes[i][j] == -1) {
                calc_subtree_size(adj[i][j], i, j, adj, subsizes);
            }
        }
    }
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        bool ok = 1;
        for(int j = 0; j < subsizes[i].size(); j++) {
            if(subsizes[i][j] > n / 2) {
                ok = 0;
            }
        }
        if(ok) {
            ans.push_back(i);
        }
    }
    return ans;
}