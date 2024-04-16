const int MAXN = 2e5;

int low[MAXN];
int times[MAXN];
bool vis[MAXN];

void dfs(int i, vector<vector<int>> &adj, stack<int> &s, int &time, vector<vector<int>> &sccs) {
    times[i] = time;    
    low[i] = time++;
    s.push(i);
    vis[i] = 1;

    for(int x : adj[i]) {
        if(times[x] == -1) {
            dfs(x,adj,s,time,sccs);
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
    vector<vector<int>> sccs;
    fill(times, times + n, -1);
    fill(low, low + n, 0);
    fill(vis, vis + n, 0);
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(times[i] == -1) {
            dfs(i,adj,s,time,sccs);
        }
    }
    return sccs;
}