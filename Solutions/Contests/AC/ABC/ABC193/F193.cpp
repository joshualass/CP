#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};
 
struct Dinic {
    const long long flow_inf = 1e18;
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
 
    void add_edge(int v, int u, long long cap) {
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
 
    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }
 
    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    // vector<unordered_map<int,int>> g(n * n + 2);
    int s = n * n, t = n * n + 1;
    Dinic g(n * n + 2, s, t);

    vector<int> dx = {1, -1, 0, 0}, dy = {0, 0, 1, -1};

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if((i + j) & 1) {
                if(a[i][j] == 'B') {
                    a[i][j] = 'W';
                } else if(a[i][j] == 'W') {
                    a[i][j] = 'B';
                }
            }
            if(a[i][j] == 'B') {
                // g[i * n + j][t] = 1e9;
                g.add_edge(i * n + j, t, 1e9);
            }
            if(a[i][j] == 'W') {
                // g[s][i * n + j] = 1e9;
                g.add_edge(s, i * n + j, 1e9);
            }
            for(int k = 0; k < 4; k++) {
                int ni = i + dx[k], nj = j + dy[k];
                if(ni >= 0 && ni < n && nj >= 0 && nj < n) {
                    // g[i * n + j][ni * n + nj] = 1;
                    g.add_edge(i * n + j, ni * n + nj, 1);
                }
            }
        }
    }

    // cout << n * (n - 1) * 2 - edmondsKarp(g, s, t) << '\n';
    cout << n * (n - 1) * 2 - g.flow() << '\n';

    return 0;
}
