#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
ll MOD;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void dfs(int i, int p, vector<vector<int>> &adj, vector<bool> &visited) {
    if(visited[i]) return;
    visited[i] = 1;
    for(auto node : adj[i]) {
        if(node != p) dfs(node, i, adj, visited);
    }
}

ll recur(int i, vector<int> &in, vector<array<ll,3>> &edges, int n) {
    if(in.size() == n - 1) {
        vector<vector<int>> adj(n);
        ll score = 0;
        for(int j = 0; j < in.size(); j++) {
            adj[edges[in[j]][1]].push_back(edges[in[j]][2]);
            adj[edges[in[j]][2]].push_back(edges[in[j]][1]);
            score += edges[in[j]][0];
            if(score >= MOD) score %= MOD;
        }
        vector<bool> visited(n);
        dfs(0,-1,adj,visited);
        // cout << "trying in : " << in << '\n';
        if(count(visited.begin(), visited.end(),1) == n) {
            return score;
        } else {
            return MOD - 1;
        }
    }
    if(i >= edges.size()) return MOD - 1;
    in.push_back(i);
    ll ans = recur(i+1,in,edges,n);
    in.pop_back();
    return min(ans, recur(i+1,in,edges,n));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m >> MOD;

    vector<array<ll,3>> edges;
    for(int i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        edges.push_back({w,u,v});
    }
    vector<int> in;
    cout << recur(0, in, edges, n) << '\n';

    return 0;
}