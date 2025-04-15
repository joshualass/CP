#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<class T>
pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>> graph, int source, int sink) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<unordered_map<int,int>> g(n);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u][v]++;
        g[v][u]++;
    }    

    auto [f, temp] = edmondsKarp(g, 0, n - 1);
    auto trace = temp;

    vector<int> s(n);

    auto dfs = [&](auto self, int i) -> void {
        if(s[i]) return;
        s[i] = 1;
        for(auto [to, w] : g[i]) {
            if(trace[i][to] == 0) self(self, to);
        }
        for(int j = 0; j < n; j++) {
            if(trace[j][i] > 0) self(self, j);
        }
    };

    dfs(dfs, 0);

    vector<array<int,2>> res;
    for(int i = 0; i < n; i++) {
        if(s[i]) {
            for(auto [to, w]: g[i]) {
                if(trace[i][to] > 0 && s[to] == 0) {
                    res.push_back({i + 1, to + 1});
                }
            }
        }
    }

    cout << res.size() << '\n';
    for(auto edge : res) cout << edge[0] << " " << edge[1] << '\n';

    return 0;
}
