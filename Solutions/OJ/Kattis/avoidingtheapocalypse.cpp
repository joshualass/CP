#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

// template<class T>
// T edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<int> par(graph.size());
//     vector<int> q = par;

//     for(;;) {
//         fill(par.begin(), par.end(), -1);
//         par[source] = 0;
//         int ptr = 1;
//         q[0] = source;

//         for(int i = 0; i < ptr; i++) {
//             int x = q[i];
//             for(auto e : graph[x]) {
//                 if(par[e.first] == -1 && e.second > 0) {
//                     par[e.first] = x;
//                     q[ptr++] = e.first;
//                     if(e.first == sink) goto out;
//                 }
//             }
//         }
//     return flow;
// out:
//     T inc = numeric_limits<T>::max();
//     for(int y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(int y = sink; y != source; y = par[y]) {
//         int p = par[y];
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         }
//     }
// }

struct FlowEdge {
    int v, u;
    int cap, flow = 0;
    FlowEdge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};
 
struct Dinic {
    const int flow_inf = 200;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;
 
    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }
 
    void add_edge(int v, int u, int cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
 
    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }
 
    int dfs(int v, int pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
 
    int flow() {
        int f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (int pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

void solve() {
    int n, i, g, s, m; cin >> n >> i >> g >> s >> m;
    i--;
    int source = n * (s + 2);
    int sink = n * (s + 1);

    // vector<unordered_map<int,int>> adj(n * (s + 1) + 1);
    Dinic d(n * (s + 2) + 1,source,sink);
    d.add_edge(source, i, g);

    for(int j = 0; j < n; j++) {
        for(int t = 0; t < s; t++) {
            // adj[n * t + j][n * (t + 1) + j] = 100;
            d.add_edge(n*t+j,n*(t+1)+j,100);
        }
    }

    for(int j = 0; j < m; j++) {
        int x; cin >> x;
        x--;
        // adj[n * s + x][sink] = 100;
        d.add_edge(n*s+x,sink,100);
    }

    int r; cin >> r;
    for(int j = 0; j < r; j++) {
        int a, b, p, t; cin >> a >> b >> p >> t;
        a--; b--;
        for(int z = 0; z + t <= s; z++) {
            // adj[n * z + a][n * (z + t) + b] = p;
            d.add_edge(n*z+a,n*(z+t)+b,p);
        }
    }
    // cout << min(g, edmondsKarp(adj,source,sink)) << '\n';
    cout << d.flow() << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}