#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int N = 1e5;

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

    int n, k; cin >> n >> k;
    vector<int> a(N + 1), b(N + 1);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x]++;
    }
    for(int i = 0; i < k; i++) {
        int x; cin >> x;
        b[x]++;
    }

    int s = N * 2, t = N * 2 + 1;

    Dinic d(N * 2 + 2, s, t);
    for(int i = 1; i <= N; i++) {
        d.add_edge(s, i - 1, a[i]);
        d.add_edge(N + i - 1, t, b[i]);
    }

    for(int i = 1; i <= N; i++) {
        for(int j = 1; i * j <= N; j++) {
            d.add_edge(i * j - 1, N + i - 1, min(n, k));
        }
    }

    cout << d.flow() << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()
// const int N = 1e5;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, k; cin >> n >> k;
//     vector<int> a(N + 1), b(N + 1);
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         a[x]++;
//     }

//     for(int i = 0; i < k; i++) {
//         int x; cin >> x;
//         b[x]++;
//     }

//     int res = 0;

//     // for(int i = N; i >= 1; i--) {
//     for(int i = 1; i <= N; i++) {
//         for(int j = 1; i * j <= N; j++) {
//             int sub = min(b[i], a[j * i]);
//             b[i] -= sub;
//             a[j] -= sub;
//             res += sub;
//         }
//     }

//     cout << res << '\n';

//     return 0;
// }
