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