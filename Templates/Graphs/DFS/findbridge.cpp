void dfsb(int i, int p, vector<vector<int>> &adj, vector<int> &low, vector<int> &d, int &time) {
    d[i] = time++;
    low[i] = d[i];

    for(int x : adj[i]) {
        if(x != p) {
            if(d[x] == -1) {
                dfsb(x,i,adj,low,d,time);
            }
            // if()
            low[i] = min(low[i], low[x]);
        }
    }

}

vector<vector<int>> find_bridges(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<int> low(n,-1);
    vector<int> d(n,-1);
    int time = 0;

    for(int i = 0; i < n; i++) {
        if(d[i] == -1) {
            dfsb(i,-1,adj,low,d,time);
        }
    }

    vector<vector<int>> res(n);
    for(int i = 0; i < adj.size(); i++) {
        for(int x : adj[i]) {
            if(low[x] > d[i]) {
                res[x].push_back(i);
                res[i].push_back(x);
            }
        }
    }

    return res;
}
