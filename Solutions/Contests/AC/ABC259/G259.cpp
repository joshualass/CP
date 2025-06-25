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

    int h, w; cin >> h >> w;

    vector<vector<ll>> a(h, vector<ll>(w));
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<unordered_map<int,ll>> g(h + w + 2);
    int s = h + w, t = h + w + 1;

    ll res = 0;

    for(int i = 0; i < h; i++) {
        ll sum = 0;
        for(int j = 0; j < w; j++) {
            sum += a[i][j];
        }
        ll A = -sum, B = 0;
        ll lo = min(A, B);
        A -= lo;
        B -= lo;
        res -= lo;
        g[s][i] += A;
        g[i][t] += B;
    }

    for(int j = 0; j < w; j++) {
        ll sum = 0;
        for(int i = 0; i < h; i++) {
            sum += a[i][j];
        }
        ll A = 0, B = -sum;
        ll lo = min(A, B);
        A -= lo;
        B -= lo;
        res -= lo;
        g[s][h + j] = A;
        g[h + j][t] = B;
    }

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(a[i][j] < 0) g[h + j][i] = 1e18;
            if(a[i][j] > 0) g[h + j][i] = a[i][j];
        }
    }

    // cout << "flow : " << edmondsKarp(g, s, t) << '\n';

    res -= edmondsKarp(g, s, t);

    cout << res << '\n';

    return 0;
}
