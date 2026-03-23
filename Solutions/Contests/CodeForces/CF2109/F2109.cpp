#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

const ll inf = 1e18;

void solve() {
    
    ll n, r, k; cin >> n >> r >> k;
    r--;
    vector a(n, vector<ll>(n));
    vector<string> c(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    for(auto &x : c) cin >> x;

    vector<ll> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};

    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    vector vis(n, vector<ll>(n)), dist(n, vector<ll>(n, 1e9));
    ll dism = 0;

    auto add_q_ = [&](ll nx, ll ny) -> void {
        if(a[nx][ny] < dist[nx][ny]) {
            pq.push({a[nx][ny], nx, ny});
            dist[nx][ny] = a[nx][ny];
        }
    };

    add_q_(0, 0);

    while(pq.size() && vis[r][n-1] == 0) {
        auto [dis, x, y] = pq.top();
        pq.pop();
        // cout << "dis : " << dis << " x : " << x << " y : " << y << '\n';
        if(vis[x][y] || dist[x][y] < dis) continue;
        vis[x][y] = 1;
        // cout << "visiting\n";
        dism = max(dism, dist[x][y]);
        for(ll i = 0; i < 4; i++) {
            ll nx = x + dx[i], ny = y + dy[i];
            if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
                add_q_(nx, ny);
            }
        }
    }

    // cout << "dism : " << dism << '\n';

    vector mpath(n, vector<ll>(n));

    ll cx = 0, cy = 0, cdir = 0;
    while(1) {
        mpath[cx][cy] = 1;
        if(cx == r && cy == n - 1) break;
        ll nx = cx + dx[cdir], ny = cy + dy[cdir];
        if(nx >= 0 && nx < n && ny >= 0 && ny < n && a[nx][ny] <= dism) {
            cx = nx, cy = ny;
            cdir = (cdir + 3) % 4;
        } else {
            cdir = (cdir + 1) % 4;
        }
    }

    // cout << "mpath\n";

    // for(auto ro : mpath) cout << ro << '\n';

    for(ll i = -1; i <= 1; i += 2) for(ll j = -1; j <= 1; j+= 2) {
        dx.push_back(i);
        dy.push_back(j);
    }

    ll lo = 1, hi = 1e6;
    vector<vector<ll>> d(n, vector<ll>(n));
    while(lo != hi) {
        ll m = (lo + hi + 1) / 2;
        priority_queue<array<ll,3>,vector<array<ll,3>>,greater<array<ll,3>>> pq;
        for(ll i = 0; i < n; i++) for(ll j = 0; j < n; j++) d[i][j] = inf;
        auto add_q = [&](ll i, ll j, ll cd) -> void {
            ll dis;
            if(a[i][j] >= m) {
                dis = cd;
            } else {
                if(c[i][j] == '0') {
                    dis = inf;
                } else {
                    if(mpath[i][j] == 0 || m <= dism) {
                        dis = cd + m - a[i][j];
                    } else {
                        dis = inf;
                    }
                }
            }
            dis = min(dis, inf);
            if(dis < d[i][j]) {
                d[i][j] = dis;
                pq.push({dis, i, j});
            }
        };

        for(ll i = 0; i < n; i++) {
            add_q(i, 0, 0);
            add_q(0, i, 0);
        }
        for(ll i = 0; i <= r; i++) add_q(i, n - 1, 0);

        while(sz(pq)) {
            auto [k, i, j] = pq.top();
            pq.pop();
            // cout << "dis : " << k << " i : " << i << " j : " << j << endl;
            for(ll l = 0; l < 8; l++) {
                ll ni = i + dx[l], nj = j + dy[l];
                if(ni >= 0 && ni < n && nj >= 0 && nj < n) add_q(ni, nj, k);
            }
        }
        ll best = inf;
        for(ll i = r; i < n; i++) best = min(best, d[i][n-1]);
        for(ll i = 0; i < n; i++) best = min(best, d[n-1][i]);
        // cout << "m : " << m << " best : " << best << endl;
        // for(auto x : d) cout << x << endl;
        if(best <= k) {
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

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// max flow is too slow
// */

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// struct FlowEdge {
//     ll v, u;
//     long long cap, flow = 0;
//     FlowEdge(ll v, ll u, long long cap) : v(v), u(u), cap(cap) {}
// };
 
// struct Dinic {
//     const long long flow_inf = 1e18;
//     vector<FlowEdge> edges;
//     vector<vector<ll>> adj;
//     ll n, m = 0;
//     ll s, t;
//     vector<ll> level, ptr;
//     queue<ll> q;
 
//     Dinic(ll n, ll s, ll t) : n(n), s(s), t(t) {
//         adj.resize(n);
//         level.resize(n);
//         ptr.resize(n);
//     }
 
//     void add_edge(ll v, ll u, long long cap) {
//         edges.emplace_back(v, u, cap);
//         edges.emplace_back(u, v, 0);
//         adj[v].push_back(m);
//         adj[u].push_back(m + 1);
//         m += 2;
//     }
 
//     bool bfs() {
//         while (!q.empty()) {
//             ll v = q.front();
//             q.pop();
//             for (ll id : adj[v]) {
//                 if (edges[id].cap - edges[id].flow < 1)
//                     continue;
//                 if (level[edges[id].u] != -1)
//                     continue;
//                 level[edges[id].u] = level[v] + 1;
//                 q.push(edges[id].u);
//             }
//         }
//         return level[t] != -1;
//     }
 
//     long long dfs(ll v, long long pushed) {
//         if (pushed == 0)
//             return 0;
//         if (v == t)
//             return pushed;
//         for (ll& cid = ptr[v]; cid < (ll)adj[v].size(); cid++) {
//             ll id = adj[v][cid];
//             ll u = edges[id].u;
//             if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
//                 continue;
//             long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
//             if (tr == 0)
//                 continue;
//             edges[id].flow += tr;
//             edges[id ^ 1].flow -= tr;
//             return tr;
//         }
//         return 0;
//     }
 
//     long long flow() {
//         long long f = 0;
//         while (true) {
//             fill(level.begin(), level.end(), -1);
//             level[s] = 0;
//             q.push(s);
//             if (!bfs())
//                 break;
//             fill(ptr.begin(), ptr.end(), 0);
//             while (long long pushed = dfs(s, flow_inf)) {
//                 f += pushed;
//             }
//         }
//         return f;
//     }
// };

// template<class T>
// T edmondsKarp(vector<unordered_map<ll,T>>& graph, ll source, ll sink) {
//     assert(source != sink);
//     T flow = 0;
//     vector<ll> par(graph.size());
//     vector<ll> q = par;

//     for(;;) {
//         fill(par.begin(), par.end(), -1);
//         par[source] = 0;
//         ll ptr = 1;
//         q[0] = source;

//         for(ll i = 0; i < ptr; i++) {
//             ll x = q[i];
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
//     for(ll y = sink; y != source; y = par[y]) {
//         inc = min(inc, graph[par[y]][y]);
//     }

//     flow += inc;
//     for(ll y = sink; y != source; y = par[y]) {
//         ll p = par[y];
//         if((graph[p][y] -= inc) <= 0) {
//             graph[p].erase(y);
//         }
//         graph[y][p] += inc;
//         }
//     }
// }

// void solve() {
    
//     ll n, r, k; cin >> n >> r >> k;
//     r--;
//     vector a(n, vector<ll>(n));
//     vector<string> c(n);
//     for(auto &x : a) for(auto &y : x) cin >> y;
//     for(auto &x : c) cin >> x;

//     vector<ll> dx = {0, 1, 0, -1}, dy = {1, 0, -1, 0};

//     priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
//     vector vis(n, vector<ll>(n)), dist(n, vector<ll>(n, 1e9));
//     ll dism = 0;

//     auto add_q = [&](ll nx, ll ny) -> void {
//         if(a[nx][ny] < dist[nx][ny]) {
//             pq.push({a[nx][ny], nx, ny});
//             dist[nx][ny] = a[nx][ny];
//         }
//     };

//     add_q(0, 0);

//     while(pq.size() && vis[r][n-1] == 0) {
//         auto [dis, x, y] = pq.top();
//         pq.pop();
//         // cout << "dis : " << dis << " x : " << x << " y : " << y << '\n';
//         if(vis[x][y] || dist[x][y] < dis) continue;
//         vis[x][y] = 1;
//         // cout << "visiting\n";
//         dism = max(dism, dist[x][y]);
//         for(ll i = 0; i < 4; i++) {
//             ll nx = x + dx[i], ny = y + dy[i];
//             if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
//                 add_q(nx, ny);
//             }
//         }
//     }

//     // cout << "dism : " << dism << '\n';

//     vector mpath(n, vector<ll>(n));

//     ll cx = 0, cy = 0, cdir = 0;
//     while(1) {
//         mpath[cx][cy] = 1;
//         if(cx == r && cy == n - 1) break;
//         ll nx = cx + dx[cdir], ny = cy + dy[cdir];
//         if(nx >= 0 && nx < n && ny >= 0 && ny < n && a[nx][ny] <= dism) {
//             cx = nx, cy = ny;
//             cdir = (cdir + 3) % 4;
//         } else {
//             cdir = (cdir + 1) % 4;
//         }
//     }

//     // cout << "mpath\n";

//     // for(auto ro : mpath) cout << ro << '\n';

//     ll lo = 0, hi = 2e6;
//     vector<unordered_map<ll,ll>> g(n * n * 2 + 2);
//     while(lo != hi) {
//         ll m = (lo + hi + 1) / 2;

//         ll s = n * n * 2, t = n * n * 2 + 1;
//         // Dinic d(n * n * 2 + 2, s, t);

//         for(ll i = 0; i < n; i++) {
//             for(ll j = 0; j < n; j++) {
//                 ll flow;
//                 if(a[i][j] < m) { //need to take action or have unlimited flow
//                     if(c[i][j] == '0') {
//                         flow = 1e9;
//                     } else {
//                         if(mpath[i][j]) {
//                             if(m > dism) {
//                                 flow = 1e9;
//                             } else {
//                                 flow = m - a[i][j];
//                             }
//                         } else {
//                             flow = m - a[i][j];
//                         }
//                     }
//                 } else { //blocked up
//                     flow = 0;
//                 }
//                 // d.add_edge(i * n + j, n * n + i * n + j, flow);
//                 g[i * n + j][n * n + i * n + j] = flow;
//                 for(ll k = 0; k < 4; k++) {
//                     ll ni = i + dx[k], nj = j + dy[k];
//                     if(ni >= 0 && ni < n && nj >= 0 && nj < n) {
//                         // d.add_edge(n * n + i * n + j, ni * n + nj, 1e9);
//                         g[n * n + i * n + j][ni * n + nj] = 1e9;
//                     }
//                 }
//             }
//         }

//         // d.add_edge(s, (n - 1) * n, k + 1);
//         // d.add_edge(n * n + r * n + n - 1, t, k + 1);
//         g[s][(n - 1) * n] = k + 1;
//         g[n * n + r * n + n - 1][t] = k + 1;

//         // ll flow = d.flow();
//         ll flow = edmondsKarp(g, s, t);
//         // cout << "m : " << m << " flow : " << flow << '\n';
//         if(flow <= k) {
//             lo = m;
//         } else {
//             hi = m - 1;
//         }

//     }

//     cout << dism << " " << lo << '\n';


// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }