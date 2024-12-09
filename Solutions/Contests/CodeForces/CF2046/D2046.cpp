#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
//not in the range. 

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

void solve() {
    int n, m; cin >> n >> m;

    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    vector<unordered_map<int,int>> graph(n * 2 + 2);
    int s = n * 2, t = n * 2 + 1;

    for(int i = 0; i < n; i++) {
        graph[s][i * 2 + 1] = a[i] + 1;
        graph[i * 2][i * 2 + 1] = 200;
        graph[i * 2][t] = 1;
        for(int x : adj[i]) {
            graph[i * 2 + 1][x * 2] = 200;
        }
    }

    int messengers = 0;
    while(1) {
        auto [flow, trace] = edmondsKarp(graph, s, t);
        // cout << "messengers : " << messengers << " flow : " << flow << '\n';
        if(flow + messengers == n) break;
        messengers++;
        for(int i = 0; i < n; i++) {
            if(trace[i][t] == 0) {
                graph[i * 2].erase(t);
                graph[s][i * 2 + 1] = a[i];
                break;
            }
        }
    }

    cout << messengers << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();    

    return 0;
}