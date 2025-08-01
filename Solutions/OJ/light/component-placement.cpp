#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e12;

/*
very direct application of the a, b, c costs for min-cut stuff.
max-flow still pretty challenging. 
*/

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

void solve() {
    
    int n, m; cin >> n >> m;

    vector<int> x(n), y(n);
    for(int &z : x) cin >> z;
    for(int &z : y) cin >> z;

    int s = n, t = n + 1;

    Dinic d(n + 2, s, t);
    for(int i = 0; i < n; i++) {
        ll a = x[i], b = y[i];
        int p; cin >> p;
        if(p == -1) {
            a += inf;
        }
        if(p == 1) {
            b += inf;
        }
        d.add_edge(s, i, a);
        d.add_edge(i, t, b);
    }

    for(int i = 0; i < m; i++) {
        int p, q, r; cin >> p >> q >> r;
        p--; q--;
        d.add_edge(p, q, r);
        d.add_edge(q, p, r);
    }

    cout << d.flow() << '\n';

}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 1; i <= casi; i++) {
        cout << "Case " << i << ": ";
        solve();
    }
    return 0;
}