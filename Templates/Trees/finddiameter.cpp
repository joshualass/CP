// {distance, a}
array<int,2> dfs(int i, int p, int d, vector<vector<int>> &adj) {
    array<int,2> res = {d, i};
    for(int c : adj[i]) {
        if(c != p) {
            res = max(res, dfs(c,i,d+1,adj));
        }
    }
    return res;
}

bool find_path(int i, int p, int dest, vector<vector<int>> &adj, vector<int> &path) {
    if(i == dest) {
        path.push_back(i);
        return 1;
    }

    for(int c : adj[i]) {
        if(c != p) {
            if(find_path(c,i,dest,adj,path)) {
                path.push_back(i);
                return 1;
            }
        }
    }

    return 0;
}

//{{a, b, diameter}, path}
pair<array<int,3>,vector<int>> find_diameter(vector<vector<int>> &adj) {
    array<int,2> a = dfs(0,-1,0,adj);
    array<int,2> b = dfs(a[1],-1,0,adj);
    vector<int> path;
    find_path(a[1], -1, b[1], adj, path);
    return {{a[1], b[1], b[0]}, path};
}