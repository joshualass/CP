#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
    
    int n; cin >> n;
    int s = n + 60, t = n + 61;
    Dinic d(n + 60 + 2, s, t);
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        d.add_edge(s, i, 1);
        for(int j = 0; j < 60; j++) {
            if((x >> j) & 1) d.add_edge(i, n + j, 6767);
        }
    }
    for(int i = 0; i < 60; i++) d.add_edge(n + i, t, 1);

    cout << n - d.flow() << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// /*
// there is a nicer solution
// we pretty much include every element but say that every element does not include one more bit than there already are.
// In this case, we can just exclude this element or include it and subtract 1
// this is where maxflow comes in handy
// we include all the elements, but cap the elements that would include more than one bit.
// maxflow on the bits that the elements take ... ?
// maybe editorial has a better explanation. 
// */

// template<class T>
// pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<int> par(graph.size());
//     vector<int> q = par;
//     vector<unordered_map<int,T>> trace(graph.size());

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
//     return {flow,trace};
// out:
//     T inc = numeric_limits<T>::max();
//     for(int y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(int y = sink; y != source; y = par[y]) {
//         int p = par[y];
//         trace[p][y] += inc;
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         trace[y][p] -= inc;
//         }
//     }
// }

// void solve() {
//     int n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;
//     vector<int> bad(60);

//     auto findbad = [&]() -> int {
//         vector<unordered_map<int,int>> adj(n + 62);
//         int sc = n + 60, sk = n + 61;
//         for(int i = 0; i < 60; i++) {
//             if(bad[i] == 0) {
//                 adj[sc][i+n] = 1;
//             }
//         }

//         for(int i = 0; i < n; i++) {
//             int canr = 1;
//             for(int j = 0; j < 60; j++) {
//                 if((a[i] >> j) & 1) {
//                     if(bad[j]) {
//                         canr = 0;
//                     }
//                     adj[n+j][i] = 1;
//                 }
//             }
//             if(canr) {
//                 adj[i][sk] = 1;
//             }
//         }
//         auto [flow, trace] = edmondsKarp(adj, sc, sk);
//         int upd = 0;
//         for(int i = 0; i < 60; i++) {
//             if(bad[i] == 0 && trace[i+n].empty()) {
//                 upd = 1;
//                 bad[i] = 1;
//             }
//         }
//         return upd;
//     };

//     while(findbad());

//     ll res = 0, o = 0;
//     for(int i = 0; i < n; i++) {
//         int f = 1;
//         for(int j = 0; j < 60; j++) {
//             if(((a[i] >> j) & 1) && bad[j]) {
//                 f = 0;
//             }
//         }
//         if(f) {
//             res++;
//             o |= a[i];
//         }
//     }
//     cout << res - __builtin_popcountll(o) << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

//original guessforces idea breaks from first hand-generated testcase. bad guessforces
// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
//     int n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;

//     auto getscore = [&](vector<int> bads) -> int {
//         int cnt = 0;
//         ll o = 0;
//         for(int i = 0; i < n; i++) {
//             int ok = 1;
//             for(int bad : bads) {
//                 if((a[i] >> bad) & 1) {
//                     ok = 0;
//                 }
//             }
//             if(ok) {
//                 o |= a[i];
//                 cnt++;
//             }
//         }
//         return cnt - __builtin_popcountll(o);
//     };

//     int startscore = getscore({});
//     vector<int> bads;
//     for(int i = 0; i < 60; i++) {
//         if(getscore({i}) > startscore) {
//             bads.push_back(i);
//         }
//     }

//     cout << "bads : " << bads << '\n';

//     cout << getscore(bads) << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }