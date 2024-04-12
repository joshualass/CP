#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

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

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1}; //UP, DOWN, RIGHT, LEFT

// int dx[8]{-1, -1, -1, 0, 0, 1, 1, 1}, dy[8]{-1, 0, 1, -1, 1, -1, 0, 1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int r, c; cin >> r >> c;
    vector<unordered_map<int,ll>> adj(r * c * 2 + 2);
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            ll num; cin >> num;
            adj[(i * c + j) * 2].insert({(i * c + j) * 2 + 1, num});
            for(int k = 0; k < 4; k++) {
                int ti = i + dx[k];
                int tj = j + dy[k];
                if(ti >= 0 && ti < r && tj >= 0 && tj < c) {
                    adj[(i * c + j) * 2 + 1].insert({(ti * c + tj) * 2, INF});
                }
            }
            // adj[r * c * 2].insert({(i * c + j) * 2,INF});
            if(i == 0 || j == 0 || i == r - 1 || j == c - 1) {
                adj[(i * c + j) * 2 + 1].insert({r * c * 2 + 1, INF});
            }
        }
    }
    int sr, sc; cin >> sr >> sc;
    adj[r * c * 2].insert({(sr * c + sc) * 2,INF});
    ll res = edmondsKarp(adj,r * c * 2, r * c * 2 + 1);
    cout << res << '\n';

    return 0;
}