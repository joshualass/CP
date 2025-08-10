#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, unordered_map<T,D> m) {
    for(auto &x: m) os << '(' << x.first << ", " << x.second << ") ";
    return os;
}

template<class T>
pair<T,vector<unordered_map<int,T>>> edmondsKarp(vector<unordered_map<int,T>>& graph, int source, int sink) {
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
        int a, b; cin >> a >> b;
        g[a-1][b-1]++;
    }

    auto [flow, ttrace] = edmondsKarp(g, 0, n - 1);
    auto trace = ttrace;

    // for(int i = 0; i < n; i++) cout << "i : " << i << " trace[i] : " << trace[i] << '\n';
    
    auto dfs = [&](auto self, int i, vector<int> &path) -> void {
        path.push_back(i);
        if(i == n - 1) return;
        while(trace[i].size()) {
            int k = trace[i].begin()->first;
            if(trace[i][k] > 0) {
                trace[i][k]--;
                self(self, k, path);
                break;
            } else {
                trace[i].erase(k);
            }
        }
    };

    cout << flow << '\n';

    for(int i = 0; i < flow; i++) {
        vector<int> path;
        dfs(dfs, 0, path);
        cout << path.size() << '\n';
        for(int j = 0; j < path.size(); j++) cout << path[j] + 1 << " \n"[j == path.size() - 1];
    }


    return 0;
}
