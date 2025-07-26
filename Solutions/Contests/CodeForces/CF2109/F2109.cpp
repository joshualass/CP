#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
max flow is too slow
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

template<class T>
T edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
    assert(source != sink);
    T flow = 0;
    vector<int> par(graph.size());
    vector<int> q = par;

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
    return flow;
out:
    T inc = numeric_limits<T>::max();
    for(int y = sink; y != source; y = par[y]) {
        inc = min(inc, graph[par[y]][y]);
    }

    flow += inc;
    for(int y = sink; y != source; y = par[y]) {
        int p = par[y];
        if((graph[p][y] -= inc) <= 0) {
            graph[p].erase(y);
        }
        graph[y][p] += inc;
        }
    }
}

void solve() {
    
    int n, r, k; cin >> n >> r >> k;
    r--;
    vector a(n, vector<int>(n));
    vector<string> c(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : c) cin >> x;

    vector<int> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};

    priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>> pq;
    vector vis(n, vector<int>(n)), dist(n, vector<int>(n, 1e9));
    int dism = 0;

    auto add_q = [&](int nx, int ny) -> void {
        if(a[nx][ny] < dist[nx][ny]) {
            pq.push({a[nx][ny], nx, ny});
            dist[nx][ny] = a[nx][ny];
        }
    };

    add_q(0, 0);

    while(pq.size() && vis[r][n-1] == 0) {
        auto [dis, x, y] = pq.top();
        pq.pop();
        // cout << "dis : " << dis << " x : " << x << " y : " << y << '\n';
        if(vis[x][y] || dist[x][y] < dis) continue;
        vis[x][y] = 1;
        // cout << "visiting\n";
        dism = max(dism, dist[x][y]);
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
                add_q(nx, ny);
            }
        }
    }

    // cout << "dism : " << dism << '\n';

    vector mpath(n, vector<int>(n));

    int cx = 0, cy = 0, cdir = 0;
    while(1) {
        mpath[cx][cy] = 1;
        if(cx == r && cy == n - 1) break;
        int nx = cx + dx[cdir], ny = cy + dy[cdir];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && a[nx][ny] <= dism) {
            cx = nx, cy = ny;
            cdir = (cdir + 3) % 4;
        } else {
            cdir = (cdir + 1) % 4;
        }
    }

    // cout << "mpath\n";

    // for(auto ro : mpath) cout << ro << '\n';

    int lo = 0, hi = 2e6;
    vector<unordered_map<int,int>> g(n * n * 2 + 2);
    while(lo != hi) {
        int m = (lo + hi + 1) / 2;

        int s = n * n * 2, t = n * n * 2 + 1;
        // Dinic d(n * n * 2 + 2, s, t);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                int flow;
                if(a[i][j] < m) { //need to take action or have unlimited flow
                    if(c[i][j] == '0') {
                        flow = 1e9;
                    } else {
                        if(mpath[i][j]) {
                            if(m > dism) {
                                flow = 1e9;
                            } else {
                                flow = m - a[i][j];
                            }
                        } else {
                            flow = m - a[i][j];
                        }
                    }
                } else { //blocked up
                    flow = 0;
                }
                // d.add_edge(i * n + j, n * n + i * n + j, flow);
                g[i * n + j][n * n + i * n + j] = flow;
                for(int k = 0; k < 4; k++) {
                    int ni = i + dx[k], nj = j + dy[k];
                    if(ni >= 0 && ni < n && nj >= 0 && nj < n) {
                        // d.add_edge(n * n + i * n + j, ni * n + nj, 1e9);
                        g[n * n + i * n + j][ni * n + nj] = 1e9;
                    }
                }
            }
        }

        // d.add_edge(s, (n - 1) * n, k + 1);
        // d.add_edge(n * n + r * n + n - 1, t, k + 1);
        g[s][(n - 1) * n] = k + 1;
        g[n * n + r * n + n - 1][t] = k + 1;

        // ll flow = d.flow();
        int flow = edmondsKarp(g, s, t);
        // cout << "m : " << m << " flow : " << flow << '\n';
        if(flow <= k) {
            lo = m;
        } else {
            hi = m - 1;
        }

    }

    cout << dism << " " << lo << '\n';


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}