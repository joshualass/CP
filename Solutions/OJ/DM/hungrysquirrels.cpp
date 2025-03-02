#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<class T>
pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vector<int> par(graph.size());
    vector<int> q = par;
    vector<unordered_map<int,T>> trace(graph.size());

    for(;;) {
        fill(par.begin(), par.end(), -1);
        par[source] = 0;
        int ptr = 1;
        q[0] = source;

        for(int i = 0; i < ptr; i++) {
            int x = q[i];
            for(auto e : graph[x]) {
                if(par[e.first] == -1 && e.second > 0) {
                    par[e.first] = x;
                    q[ptr++] = e.first;
                    if(e.first == sink) goto out;
                }
            }
        }
    return {flow,trace};
out:
    T inc = numeric_limits<T>::max();
    for(int y = sink; y != source; y = par[y]) {
        inc = min(inc, graph[par[y]][y]);
    }

    flow += inc;
    for(int y = sink; y != source; y = par[y]) {
        int p = par[y];
        trace[p][y] += inc;
        if((graph[p][y] -= inc) <= 0) {
            graph[p].erase(y);
        }
        graph[y][p] += inc;
        trace[y][p] -= inc;
        }
    }
}

pair<bool, vector<unordered_map<int,ll>>> flowdemand(vector<unordered_map<int,array<ll,2>>> &adj, int s, int t, ll w) {
    
    int n = adj.size();
    vector<ll> indemand(n), outdemand(n);
    ll demand_sum = 0;

    vector<unordered_map<int,ll>> graph(n + 2);

    for(int i = 0; i < n; i++) {
        for(auto [to, edge] : adj[i]) {
            outdemand[i] += edge[1];
            indemand[to] += edge[1];
            graph[i][to] = edge[0] - edge[1];
            demand_sum += edge[1];
        }
    }

    int S = n, T = n + 1;
    for(int i = 0; i < n; i++) {
        if(outdemand[i]) {
            graph[i][T] = outdemand[i];
        }
        if(indemand[i]) {
            graph[S][i] = indemand[i];
        }
    }

    graph[t][s] = w;
    auto [flow, trace] = edmondsKarp(graph, S, T);
    return {flow == demand_sum, trace};
}

ll minflowdemand(vector<unordered_map<int,array<ll,2>>> &adj, int s, int t) {
    
    ll demand_sum = 0;
    int n = adj.size();
    for(int i = 0; i < n; i++) {
        for(auto [to, edge] : adj[i]) {
            demand_sum += edge[1];
        }
    }

    ll l = 0, r = demand_sum + 1;
    while(l != r) {
        ll m = (l + r) / 2;
        auto [poss, trace] = flowdemand(adj, s, t, m);
        if(poss) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if(l == demand_sum + 1) return -1;
    return l;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<int,2>> a(n), b(m);
    vector<vector<array<int,2>>> c(n, vector<array<int,2>>(m));

    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : c) for(auto &y : x) cin >> y[0];
    for(auto &x : b) for(auto &y : x) cin >> y;





    return 0;
}