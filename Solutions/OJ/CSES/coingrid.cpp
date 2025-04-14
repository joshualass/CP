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

    int n; cin >> n;

    vector<unordered_map<int,int>> g(n * 2 + 2);
    int s = n * 2, t = n * 2 + 1;

    for(int i = 0; i < n; i++) {
        string l; cin >> l;
        for(int j = 0; j < n; j++) {
            if(l[j] == 'o') g[i][j + n] = 1;
        }
        g[s][i] = 1;
        g[i+n][t] = 1;
    }

    auto [flow, temp] = edmondsKarp(g, s, t);
    auto trace = temp;
    vector<int> ss(n * 2 + 2);

    auto dfs = [&](auto self, int i) -> void {
        if(ss[i]) return; 
        ss[i] = 1;
        for(auto [to, w] : g[i]) {
            if(trace[i][to] == 0) self(self, to);
        }
        for(int j = 0; j < n * 2 + 2; j++) {
            if(trace[j][i] == 1) self(self, j);
        }
    };

    dfs(dfs, s);

    vector<array<int,2>> edges;
    for(int i = 0; i < n * 2 + 2; i++) {
        if(ss[i]) {
            for(auto [to, w] : g[i]) {
                if(ss[to] == 0) {
                    edges.push_back({i,to});
                }
            }
        }
    }

    cout << edges.size() << '\n';
    for(auto edge : edges) {
        if(edge[0] == s) {
            cout << "1 " << edge[1] + 1 << '\n';
        } else {
            cout << "2 " << edge[0] + 1 - n << '\n';
        }
    }

    return 0;
}
