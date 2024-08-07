#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll dinic(int n, vector<vector<pair<int, ll>>> c, int source, int sink) {
    ll ans = 0;
    //redo organization of edges
    vector<pair<int, ll>> edges(0);
    vector<vector<int>> adj(n, vector<int>(0));
    int m = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < c[i].size(); j++){
            int u = i;
            int v = c[i][j].first;
            ll cap = c[i][j].second;
            adj[u].push_back(m);
            adj[v].push_back(m + 1);
            edges.push_back({v, cap});
            edges.push_back({u, 0});
            m += 2;
        }
    }
    while(true) {
        //create level graph
        vector<int> level(n, -1);
        queue<int> q;
        vector<bool> v(n, false);
        v[source] = true;
        q.push(source);
        level[source] = 0;
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            for(int i = 0; i < adj[cur].size(); i++) {
                int nEdge = adj[cur][i];
                int next = edges[nEdge].first;
                if(v[next]) {
                    continue;
                }
                if(edges[nEdge].second == 0){
                    //no flow
                    continue;
                }
                v[next] = true;
                q.push(next);
                level[next] = level[cur] + 1;
            }
        }
        if(!v[sink]){
            //we're done here
            break;
        }
        while(true) {
            //do dfs until there is no path from source to sink along level graph
            stack<int> s;
            s.push(source);
            stack<int> est;
            stack<int> ist;
            ist.push(0);
            while(s.size() != 0){
                int cur = s.top();
                if(cur == sink) {   
                    //we've found path from source to sink
                    break;
                }
                bool foundNext = false;
                for(int i = ist.top(); i < adj[cur].size(); i++){
                    int nEdge = adj[cur][i];
                    int next = edges[nEdge].first;
                    if(level[next] <= level[cur]){
                        continue;
                    }
                    if(edges[nEdge].second == 0){
                        continue;
                    }
                    s.push(next);
                    est.push(nEdge);
                    ist.pop();
                    ist.push(i + 1);
                    ist.push(0);
                    foundNext = true;
                    break;
                }
                if(!foundNext) {
                    s.pop();
                    ist.pop();
                    if(est.size() != 0){
                        est.pop();
                    }
                    //mark this node as a dead end
                    level[cur] = -1;
                }
            }
            if(s.size() != 0 && s.top() == sink) {
                //found a path yay, now we update flow for edges on path
                ll bn = 1e18;
                vector<int> path(est.size(), 0);
                for(int i = 0; i < path.size(); i++){
                    path[i] = est.top();
                    est.pop();
                    bn = min(bn, edges[path[i]].second);
                }
                for(int i = 0; i < path.size(); i++){
                    //forward edge
                    edges[path[i]].second -= bn;
                    //backwards edge
                    edges[path[i] ^ 1].second += bn;
                }
                ans += bn;
            }
            else {
                //the maximum flow for this level configuration has been reached. 
                break;
            }
        }
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int R, C, T; cin >> R >> C >> T;
    int n = 2 * R * C * (T + 1) + 2;
    int source = (2 * R * C * (T + 1));
    int sink = (2 * R * C * (T + 1)) + 1;
    vector<vector<pair<int,ll>>> adj(n);
    vector<vector<char>> map(R,vector<char>(C));
    for(int r = 0; r < R; r++) {
        string line; cin >> line;
        for(int c = 0; c < C; c++) {
            map[r][c] = line[c];
        }
    }

    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            if(map[r][c] == '#') {
                continue;
            }
            if(map[r][c] == 'P') {
                adj[source].push_back({r * C + c, 1});
            }
            for(int t = 0; t <= T; t++) {
                adj[R*C*t*2 + r * C + c].push_back({R*C*(t*2 + 1) + r * C + c,1});
            }
            for(int t = 0; t < T; t++) {
                adj[R*C*(t*2 + 1) + r * C + c].push_back({R*C*((t + 1) * 2) + r * C + c, 1});
                if(map[r][c] == 'E') {
                    adj[R*C*(t*2 + 1) + r * C + c].push_back({sink,1});
                } else {
                    if(r != 0 && map[r-1][c] != '#') {
                        adj[R*C*(t*2 + 1) + r * C + c].push_back({R*C*((t + 1) * 2) + (r - 1) * C + c, 1});
                    }
                    if(c != 0 && map[r][c-1] != '#') {
                        adj[R*C*(t*2 + 1) + r * C + c].push_back({R*C*((t + 1) * 2) + r * C + (c - 1), 1});
                    }
                    if(r != R - 1 && map[r+1][c] != '#') {
                        adj[R*C*(t*2 + 1) + r * C + c].push_back({R*C*((t + 1) * 2) + (r + 1) * C + c, 1});
                    }
                    if(c != C - 1 && map[r][c+1] != '#') {
                        adj[R*C*(t*2 + 1) + r * C + c].push_back({R*C*((t + 1) * 2) + r * C + (c + 1), 1});
                    }
                }
            }
            if(map[r][c] == 'E') {
                adj[R*C*(T*2 + 1) + r * C + c].push_back({sink,1});
            }
        }
    }
    for(vector<pair<int,ll>> x : adj) {
        // cout << x.size() << "\n";
    }
    cout << dinic(n, adj, source, sink) << "\n";
    return 0;
}
