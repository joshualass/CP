#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//iterating over the edges in adj[i] is expensive, so we need to find a way to do this for each node a single time

void solve() {

    int n, m; cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<map<int,set<int>>> cadj(n);
    
    for(int i = 0; i < m; i++) {
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        adj[u].push_back({v,c});
        adj[v].push_back({u,c});
        cadj[u][c].insert(v);
        cadj[v][c].insert(u);
    }
    // cout << "here?" << endl;
    int b, e; cin >> b >> e;
    b--; e--;
    int level = 0;
    set<int> next;
    next.insert(b);
    vector<int> visited(n,INT_MAX);

    while(next.size()) {
        queue<pair<int,int>> q;
        for(int node : next) {
            visited[node] = level;
            for(pair<int,int> edge : adj[node]) {
                q.push(edge);
            }
        }
        next.clear();
        while(q.size()) {
            auto [u, c] = q.front();
            q.pop();
            if(visited[u] != INT_MAX) continue;
            next.insert(u);
            for(int to : cadj[u][c]) {
                q.push({to,c});
                cadj[to][c].erase(u);
            }
            cadj[u][c].clear();
        }
        level++;
    }
    cout << visited[e] << '\n';


    // int n, m; cin >> n >> m;
    // vector<vector<pair<int,int>>> adj(n);
    // for(int i = 0; i < m; i++) {
    //     int u, v, c; cin >> u >> v >> c;
    //     u--; v--;
    //     adj[u].push_back({v,c});
    //     adj[v].push_back({u,c});
    // }
    // vector<int> visited(n,INT_MAX);
    // vector<set<int>> cvisited(2e5+1);
    // int b, e; cin >> b >> e;
    // b--; e--;
    // priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq; //{dist,node,color}
    // pq.push({0,b,0});
    // while(pq.size()) {
    //     vector<int> v = pq.top();
    //     pq.pop();
    //     if(cvisited[v[2]].count(v[1]) || v[0] > visited[v[1]]) continue;
    //     visited[v[1]] = v[0];
    //     cvisited[v[2]].insert(v[1]);
    //     for(auto [u, c] : adj[v[1]]) {
    //         if(c == v[2]) {
    //             pq.push({v[0],u,c});
    //         } else {
    //             pq.push({v[0] + 1, u, c});
    //         }
    //     }
    // }
    // cout << visited[e] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}