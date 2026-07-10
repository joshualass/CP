#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<string> a(n);
    for(auto &x : a) cin >> x;
    
    vector<vector<int>> id(n, vector<int>(m));
    vector<array<int,2>> rev_id;
    vector<int> color;

    int p = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.') {
                id[i][j] = p++;
                color.push_back((i + j) % 2);
                rev_id.push_back({i, j});
            }
        }
    }

    vector<unordered_map<int,int>> g(p + 2);
    int s = p, t = p + 1;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.') {
                if((i + j) % 2 == 0) {
                    g[s][id[i][j]] = 1;
                    for(int d = 0; d < 4; d++) {
                        int ni = (i + dx[d]), nj = (j + dy[d]);
                        if(ni >= 0 && ni < n && nj >= 0 && nj < m && a[ni][nj] == '.') {
                            g[id[i][j]][id[ni][nj]] = 1;
                        }
                    }
                } else {
                    g[id[i][j]][t] = 1;
                }
            }
        }
    }

    ll res = 1LL * p / 2 * (p / 2 - 1);

    cerr << "res start : " << res << endl;

    if(res >= 1e6) {
        cout << "1000000\n";
        return 0;
    }

    int flow = edmondsKarp(g, s, t);
    assert(flow == p / 2);

    vector<vector<int>> adj(p);

    for(int i = 0; i < p; i++) {
        for(auto [to, flow] : g[i]) {
            if(to < s) {
                adj[to].push_back(i);
            }
        }
    }

    vector<int> vis;

    int good = 0;

    auto dfs = [&](auto self, int i) -> void {
        if(vis[i]) return;
        vis[i] = 1;

        if(color[i] == 0) {
            good++;
        }

        for(int to : adj[i]) self(self, to);
    };

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(a[i][j] == '.' && (i + j) % 2 == 0) {
                vis.assign(p, 0);
                dfs(dfs, id[i][j]);
            }
        }
    }

    cout << min(res - good + p / 2 * p / 2, 1000000LL) << '\n';

    return 0;
}
