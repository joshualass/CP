#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
//bridges are wrong
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

void spanning_dfs(int i, vector<map<int,int>> &adj, vector<bool> &visited, set<pair<int,int>> &spanning_edges) {
    visited[i] = 1;
    for(pair<int,int> p : adj[i]) {
        if(visited[p.first] == 0) {
            spanning_edges.insert({i,p.first});
            spanning_dfs(p.first, adj, visited, spanning_edges);
        }
    }
}

void bridge_dfs(int i, int p, vector<map<int,int>> &adj, vector<bool> &visited, set<pair<int,int>> &spanning_edges, set<pair<int,int>> &bridges, vector<int> &dp) {
    visited[i] = 1;
    for(pair<int,int> edge : adj[i]) {
        if(visited[edge.first]) {
            dp[i]++;
        } else {
            dp[i]--;
        }
    }
    for(pair<int,int> edge : adj[i]) {
        if(spanning_edges.count({i,edge.first})) {
            bridge_dfs(edge.first, i, adj, visited, spanning_edges, bridges, dp);
            dp[i] += dp[edge.first];
        }
    }
    if(dp[i] == 1) bridges.insert({i,p});
}

set<pair<int,int>> find_bridges(vector<map<int,int>> &adj) {
    int n = adj.size();
    set<pair<int,int>> spanning_edges;
    vector<bool> visited(n);
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            spanning_dfs(i, adj, visited, spanning_edges);
        }
    }

    visited.assign(n,0);
    set<pair<int,int>> bridges;
    vector<int> prefixes(n);
    // cout << "spanning edges : " << spanning_edges << '\n';
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            bridge_dfs(i, -1, adj, visited, spanning_edges, bridges, prefixes);
        }
    }
    return bridges;
}

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
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

    set<pair<int,int>> bridges = find_bridges(adj);
    // cout << "bridges : " << bridges << '\n';
    for(auto edge : bridges) {
        adj[edge.first].erase(edge.second);
        adj[edge.second].erase(edge.first);
    }
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
    if(s.size() == 0) {
        // cout << "goon_>.<\n";
        cout << "n:_" << n << "_g_" << smallest_edge << "_" << edge.first << "_" << edge.second << "s:";
        for(int i = 0; i < n; i++) {
            cout << i;
            for(auto edge : adj[i]) {
                cout << "_" << edge.first << "_" << edge.second;
            }
        }
        return;
    }
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