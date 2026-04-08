#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<vector<int>> r(n, vector<int>(n)), c(n, vector<int>(n));

    int id = -1;
    for(int i = 0; i < n; i++) {
        char p = 'X';
        for(int j = 0; j < n; j++) {
            if(a[i][j] != 'X') {
                if(p == 'X') {
                    id++;
                }
                r[i][j] = id;
            }
            p = a[i][j];
        }
    }

    int last_row = id;

    for(int j = 0; j < n; j++) {
        char p = 'X';
        for(int i = 0; i < n; i++) {
            if(a[i][j] != 'X') {
                if(p == 'X') {
                    id++;
                }
                c[i][j] = id;
            }
            p = a[i][j];
        }
    }

    // cout << "r" << endl;
    // for(auto x : r) cout << x << endl;

    // cout << "c" << endl;
    // for(auto x : c) cout << x << endl;

    int s = ++id;
    int t = ++id;
    vector<unordered_map<int,int>> g(id + 1);
    
    //cost of assigning a row to 1 is 1
    for(int i = 0; i <= last_row; i++) {
        g[i][t] = 1;
    }

    //cost of assigning a col to 0 is 1
    for(int i = last_row + 1; i < s; i++) {
        g[s][i] = 1;
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(a[i][j] == '-') {
                int rid = r[i][j], cid = c[i][j];
                g[cid][rid] = 1e9;
            }
        }
    }

    cout << edmondsKarp(g, s, t) << '\n';

    return 0;
}
