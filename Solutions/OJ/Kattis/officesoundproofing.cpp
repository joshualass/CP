#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

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

int dx[4]{1, -1, 0, 0}, dy[4]{0, 0, 1, -1};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<string> a(n * 2 + 1);
    for(auto &x : a) cin >> x;

    vector<vector<int>> ids(n * 2 + 1, vector<int>(n * 2 + 1));
    int p = 0;
    for(int i = 0; i < n * 2 + 1; i++) {
        for(int j = 0; j < n * 2 + 1; j++) {
            ids[i][j] = p++;
        }
    }

    int s = p++;
    int t = p++;

    vector<unordered_map<int,int>> graph(p);

    auto add_edge = [&](int u, int v, int flow) -> void {
        graph[u][v] += flow;
    };

    int reqcnt = 0;
    for(int i = 0; i < n * 2 + 1; i++) {
        for(int j = 0; j < n * 2 + 1; j++) {
            if(i % 2 == 1) {
                if(j % 2 == 1) {
                    for(int k = 0; k < 4; k++) {
                        int ni = i + dx[k], nj = j + dy[k];
                        add_edge(ids[i][j], ids[ni][nj], 1);
                    }
                    add_edge(s, ids[i][j], 1);
                } else {
                    if(j - 1 >= 0 && j + 1 < n * 2 + 1 && a[i][j-1] == 'o' && a[i][j+1] == 'o') {
                        add_edge(ids[i][j], t, 1);
                        reqcnt++;
                    }
                }
            } else {
                if(j % 2 == 1) {
                    if(i - 1 >= 0 && i + 1 < n * 2 + 1 && a[i-1][j] == 'o' && a[i+1][j] == 'o') {
                        add_edge(ids[i][j], t, 1);
                        reqcnt++;
                    }
                }
            }
        }
    }

    auto [flow, trace] = edmondsKarp(graph, s, t);
    if(flow == reqcnt) {
        cout << reqcnt << '\n';
        for(int i = 0; i < n * 2 + 1; i++) {
            for(int j = 0; j < n * 2 + 1; j++) {
                if(i % 2 == 1 && j % 2 == 1) {
                    for(int k = 0; k < 4; k++) {
                        int ni = i + dx[k], nj = j + dy[k];
                        if(trace[ids[i][j]][ids[ni][nj]]) {
                            if(k == 0) {
                                a[i+1][j] = '^';
                            } else if(k == 1) {
                                a[i-1][j] = 'v';
                            } else if(k == 2) {
                                a[i][j+1] = '<';
                            } else {
                                a[i][j-1] = '>';
                            }
                        }
                    }
                }
            }
        }
        
        for(auto x : a) cout << x << '\n';

    } else {
        cout << "impossible\n";
    }


    return 0;
}
