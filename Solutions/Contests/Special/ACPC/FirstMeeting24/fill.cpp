#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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
    vector<int> neededrow(n,m), neededcol(m,n);
    vector<string> board(n);

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        board[i] = s;
        for(int j = 0; j < m; j++) {
            if(s[j] == 'B') {
                neededrow[i]--;
                neededcol[j]--;
            }
        }
    }

    for(int &x : neededrow) x /= 2;
    for(int &y : neededcol) y /= 2;

    vector<unordered_map<int,int>> adj(n * m + n + m + 2);

    int source = n * m + n + m;
    int sink = n * m + n + m + 1;

    for(int i = 0; i < n; i++) {
        adj[source][n * m + i] += neededrow[i];
    }

    for(int i = 0; i < m; i++) {
        adj[n * m + n + i][sink] = neededcol[i];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] != 'B') {
                adj[n * m + i][i * m + j] = 1;
                adj[i * m + j][n * m + n + j] = 1;
            }
        }
    }

    // cout << "test flow : " << edmondsKarp(adj,source,sink) << '\n';

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(board[i][j] != 'B') {
                if(adj[i * m + j].count(n * m + n + j)) {
                    board[i][j] = 'X';
                } else {
                    board[i][j] = 'O';
                }

            }
        }
    }

    for(auto s : board) {
        cout << s << '\n';
    }

    return 0;
}