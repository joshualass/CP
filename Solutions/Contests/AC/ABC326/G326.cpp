#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

    vector<unordered_map<int, int>> g(n * 5 + m + 2);
    int s = n * 5 + m, t = n * 5 + m + 1;

    for(int i = 0; i < n; i++) {
        int c; cin >> c;
        for(int j = 0; j < 5; j++) {
            int cost = (j ? c : 0);
            g[s][i * 5 + j] += cost;
            g[i * 5 + j][t] = 0;
            if(j) g[i * 5 + j - 1][i * 5 + j] = 1e9;
        }
    }

    int res = 0;

    for(int i = 0; i < m; i++) {
        int a; cin >> a;
        g[s][n * 5 + i] = 0;
        g[n * 5 + i][t] = a;
        res += a;
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int l; cin >> l;
            l--;
            g[j * 5 + l][n * 5 + i] = 1e9;
        }
    }

    res -= edmondsKarp(g, s, t);

    cout << res << '\n';

    return 0;
}
