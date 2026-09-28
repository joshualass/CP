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

    ll h, w, c; cin >> h >> w >> c;

    vector<unordered_map<int,ll>> adj(h * w + 2);
    int s = h * w, t = h * w + 1;

    ll res = 0;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            ll a; cin >> a;
            res += a;
            adj[i * w + j][t] += a;
            int lp = (i == 0 || j == 0 ? s : (i - 1) * w + (j - 1));
            int rp = (i == 0 || j == w - 1 ? s : (i - 1) * w + (j + 1));
            adj[lp][i * w + j] += c;
            adj[rp][i * w + j] += c;
        }
    }

    res -= edmondsKarp(adj, s, t);

    cout << res << '\n';

    return 0;
}
