#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
//why wrong :(
void dfs(int i, int target, vector<bool> &visited, vector<map<int,int>> &adj, stack<int> &s, bool &found) {
    if(visited[i]) return;
    visited[i] = 1;
    s.push(i);
    if(i == target) found = 1;
    for(auto edge : adj[i]) {
        if(!found) {
            dfs(edge.first, target, visited, adj, s, found);
        }
    }

    if(!found) {
        s.pop();
    }
}

void solve() {
    int n, m; cin >> n >> m;
    vector<map<int,int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u][v] = w;
        adj[v][u] = w;
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(adj[i].size() == 1) q.push(i);
    }
    //prune branches
    while(q.size()) {
        int n = q.front();
        q.pop();
        for(auto [node, weight] : adj[n]) {
            adj[node].erase(n);
            // cout << "prune edge : " << node << " " << n << '\n';
            if(adj[node].size() == 1) {
                q.push(node);
            }
        }
        adj[n].clear();
    }
    //prune bridges
    


    int smallest_edge = INT_MAX;
    pair<int,int> edge = {-1,-1};
    for(int i = 0; i < n; i++) {
        for(auto e : adj[i]) {
            if(e.second < smallest_edge) {
                edge = {i, e.first};
                smallest_edge = e.second;
            }
        }
    }
    adj[edge.first].erase(edge.second);
    adj[edge.second].erase(edge.first);
    vector<bool> visited(n);
    stack<int> s;
    bool found = 0;
    dfs(edge.second, edge.first, visited, adj, s, found);
    // if(s.size() == 0) {
    //     // cout << "goon_>.<\n";
    //     cout << "n:_" << n << "_g_" << smallest_edge << "_" << edge.first << "_" << edge.second << "s:";
    //     for(int i = 0; i < n; i++) {
    //         cout << i;
    //         for(auto edge : adj[i]) {
    //             cout << "_" << edge.first << "_" << edge.second;
    //         }
    //     }
    //     return;
    // }
    cout << smallest_edge << " " << s.size() << '\n';
    while(s.size()) {
        cout << s.top() + 1 << " \n"[s.size() == 1];
        s.pop();
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}