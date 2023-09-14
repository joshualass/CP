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

    int C, R; cin >> C >> R;
    vector<vector<char>> map(R,vector<char>(C));
    vector<vector<pair<int, ll>>> adj(R*C*2+2);
    for(int r = 0; r < R; r++) {
        string line; cin >> line;
        for(int c = 0; c < C; c++) {
            map[r][c] = line[c];
        }
    }
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            if(map[r][c] == '0') {
                continue;
            }
            if(map[r][c] == 'A') {
                adj[R*C*2].push_back({r * C + c, 1e16}); //source to first A Node
                adj[r*C + c].push_back({R*C + r * C + c, 1e16}); //first A Node to second A Node
                //four directions
                if(r != 0 && map[r-1][c] != '0') {
                    adj[R * C + r * C + c].push_back({(r - 1) * C + c, 1e16});
                }
                if(c != 0 && map[r][c-1] != '0') {
                    adj[R * C + r * C + c].push_back({r * C + (c - 1), 1e16});
                }
                if(r != R -1 && map[r+1][c] != '0') {
                    adj[R * C + r * C + c].push_back({(r + 1) * C + c, 1e16});
                }
                if(c != C - 1 && map[r][c+1] != '0') {
                    adj[R * C + r * C + c].push_back({r * C + (c + 1), 1e16});
                }
            } else if(map[r][c] == 'B') {
                adj[r * C + c].push_back({R*C*2 + 1, 1e16});
            } else {
                int soldiers = map[r][c] - '0';
                adj[r*C + c].push_back({R*C + r * C + c, soldiers}); //first A Node to second A Node
                //four directions
                if(r != 0 && map[r-1][c] != '0') {
                    adj[R * C + r * C + c].push_back({(r - 1) * C + c, soldiers});
                }
                if(c != 0 && map[r][c-1] != '0') {
                    adj[R * C + r * C + c].push_back({r * C + (c - 1), soldiers});
                }
                if(r != R -1 && map[r+1][c] != '0') {
                    adj[R * C + r * C + c].push_back({(r + 1) * C + c, soldiers});
                }
                if(c != C - 1 && map[r][c+1] != '0') {
                    adj[R * C + r * C + c].push_back({r * C + (c + 1), soldiers});
                }                
            }
        }
    }
    for(vector<pair<int,ll>> x : adj) {
        // cout << x.size() << "\n";
    }
    cout << dinic(R*C*2 +2, adj, R*C*2, R*C*2 + 1) << "\n";

    return 0;
}