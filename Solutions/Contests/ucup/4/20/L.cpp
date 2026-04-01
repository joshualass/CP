#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k; cin >> n >> k;
    n *= 2;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }    

    vector<int> cols(n);

    auto dfs = [&](auto self, int i, int p, int col) -> void {
        cols[i] = col;
        for(int c : adj[i]) {
            if(c != p) self(self, c, i, col ^ 1);
        }
    };

    dfs(dfs, 0, -1, 0);

    array<int,2> sub = {}, add = {};

    if(accumulate(cols.begin(), cols.end(), 0) % 2 == k % 2) {
        int li = -1;
        for(int i = 0; i < n; i++) {
            if(sz(adj[i]) == 1) {
                li = i;
            }
        }
        sub = {li, adj[li][0]};
        int to = -1;
        for(int i = 0; i < n; i++) {
            if(i != li && cols[i] == cols[li]) {
                to = i;
            }
        }
        assert(li != -1 && to != -1);
        add = {li, to};
    } else {
        int x = adj[0][0];
        sub = {0, x};
        add = {0, x};
    }

    cout << sub[0] + 1 << " " << sub[1] + 1 << '\n';
    cout << add[0] + 1 << " " << add[1] + 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}