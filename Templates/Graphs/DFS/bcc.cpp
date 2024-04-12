//modified kosaraju's algorithm - given an undirected graph, find the biconnected components
void dfs(int i, int par, vector<vector<int>> &adj, stack<int> &s, vector<int> &times, int &time, vector<vector<int>> &sccs,vector<int> &low, vector<bool> &vis) {
    times[i] = time;    
    low[i] = time++;
    s.push(i);
    vis[i] = 1;

    for(int x : adj[i]) {
        if(x == par) {
            par = -1;
            continue;
        }
        if(times[x] == -1) {
            dfs(x,i,adj,s,times,time,sccs,low,vis);
            low[i] = min(low[i], low[x]);
        } else if(vis[x]) {
            low[i] = min(low[i], times[x]);
        }
    }

    if(low[i] == times[i]) {
        sccs.push_back({});
        while(1) {
            int w = s.top();
            s.pop();
            vis[w] = 0;
            sccs.back().push_back(w);
            if(w == i) break;
        }
    }

}

vector<vector<int>> tarjans(vector<vector<int>> adj) {
    int n = adj.size();
    stack<int> s;
    vector<int> times(n,-1);
    vector<int> low(n);
    vector<vector<int>> sccs;
    vector<bool> vis(n);
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(times[i] == -1) {
            dfs(i,-1,adj,s,times,time,sccs,low,vis);
        }
    }
    return sccs;
}