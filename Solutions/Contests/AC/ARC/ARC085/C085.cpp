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

    int n; cin >> n;
    
    vector<unordered_map<int,ll>> g(n + 2);
    int s = 0, t = n + 1;

    ll res = 0;
    for(int i = 1; i <= n; i++) {
        int a; cin >> a;
        a *= -1;
        int b = 0;
        if(a < 0) {
            res -= a;
            b -= a;
            a = 0;
        }
        g[s][i] = a;
        g[i][t] = b;
        for(int j = i * 2; j <= n; j += i) {
            g[i][j] = 1e18;
        }
    }

    res -= edmondsKarp(g, s, t);

    cout << res << '\n';

    return 0;
}
