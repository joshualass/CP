#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*

guessforces is no good here. 

1) remove all edges in the graph that will be dead ends/cannot reach the sink
    - this helps us find the mincut

nvm, copy algorithm to find min cut edges

5 8 8
1 2
1 2
2 3
1 4
1 4
4 3
3 5
3 5


*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

    int n, m, k; cin >> n >> m >> k;
    vector<unordered_map<int,int>> adj(n);
    vector<vector<int>> radj(n);
    int res = 0;

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u][v]++;
        radj[v].push_back(u);
    }

    while(1) {
        
        auto [f, temp] = edmondsKarp(adj, 0, n - 1);
        auto trace = temp;
        // cout << "flo : " << f << '\n';
        if(f > k) break;

        assert(f);

        k -= f;
        res++;

        // cout << "res : " << res << '\n';
        vector<int> s(n);

        auto dfs = [&](auto self, int i) -> void {
            if(s[i]) return;
            s[i] = 1;
            for(auto [to, w]: adj[i]) {
                if(trace[i][to] >= 0 && trace[i][to] < w) self(self, to);
            }
            for(int from : radj[i]) {
                if(trace[from][i] > 0) self(self, from);
            }
        };

        dfs(dfs, 0);

        // cout << "s : " << s << '\n';

        for(int i = 0; i < n; i++) {
            if(s[i]) {
                for(auto [to, w] : adj[i]) {
                    if(s[to] == 0) {
                        // cout << "adding edge : i " << i << " j : " << to << '\n';
                        adj[i][to] = 1000;
                    }
                }
            }
        }

    }

    cout << res << '\n';

    return 0;
}
