#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve_first() {
    int n, s; cin >> n >> s;
    s--;
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        int p = 0;
        for(int j = u; j < v; j++) {
            p ^= (s >> j) & 1;
        }
        //if parity is 1, we output high to low. 
        if(p == 1) {
            swap(u, v);
        }
        cout << u + 1 << " " << v + 1 << endl;
    }
}

void solve_second() {

    int n; cin >> n;
    vector adj(n, vector<int>(n, -1)); //wobert satisfied :D

    queue<array<int,2>> q;
    auto add_q = [&](int u, int v, int val) -> void {
        assert(u < v);
        if(adj[u][v] == -1) {
            adj[u][v] = val;
            q.push({u, v});
        }
    };

    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        int val = 0;
        if(u > v) {
            val = 1;
            swap(u, v);
        }
        add_q(u, v, val);
    }

    while(sz(q)) {
        auto [u, v] = q.front();
        q.pop();

        // cout << "u : " << u << " v : " << v << endl;

        for(int i = 0; i < u; i++) {
            if(adj[i][v] != -1) {
                int val = adj[u][v] ^ adj[i][v];
                add_q(i, u, val);
            }
            if(adj[i][u] != -1) {
                int val = adj[i][u] ^ adj[u][v];
                add_q(i, v, val);
            }
        }

        for(int i = v + 1; i < n; i++) {
            if(adj[u][i] != -1) {
                int val = adj[u][v] ^ adj[u][i];
                add_q(v, i, val);
            }
            if(adj[v][i] != -1) {
                int val = adj[u][v] ^ adj[v][i];
                add_q(u, i, val);
            }
        }
        
        for(int i = u + 1; i < v; i++) {
            if(adj[u][i] != -1) {
                int val = adj[u][v] ^ adj[u][i];
                add_q(i, v, val);
            }
            if(adj[i][v] != -1) {
                int val = adj[u][v] ^ adj[i][v];
                add_q(u, i, val);
            }
        }
    }

    // cout << "adj" << endl;
    // for(auto x : adj) {
    //     for(auto y : x) cout << y << " ";
    //     cout << endl;
    // }

    int res = 0;
    for(int i = 0; i + 1 < n; i++) {
        assert(adj[i][i+1] != -1);
        res += adj[i][i+1] << i;
    }

    cout << res + 1 << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    
    int casi; cin >> casi;
    int type; cin >> type;
    while(casi-->0) {
        if(type == 1) solve_first();
        if(type == 2) solve_second();
    }

    return 0;
}