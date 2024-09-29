#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<int,2>> edges(m);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        edges[i] = {u, v};
    }

    vector<int> removed(m,0);
    int q; cin >> q;
    vector<array<int,2>> queries(q);
    for(int i = 0; i < q; i++) {
        int c, x; cin >> c >> x;
        queries[i] = {c,x};
        if(c == 1) {
            removed[x-1] = 1;
        }
    }

    vector<int> cnts(n);
    vector<int> isalive(n);
    isalive[0] = 1;

    vector<vector<int>> adj(n);

    auto alivedfs = [&](auto self, int i) -> void {
        cnts[i]++;
        if(isalive[i]) return;
        isalive[i] = 1;
        for(int c : adj[i]) {
            self(self,c);
        }
    };

    auto addedge = [&](int u, int v) {
        adj[u].push_back(v);
        if(isalive[u]) {
            alivedfs(alivedfs, v);
        }

    };

    for(int i = 0; i < m; i++) {
        if(removed[i] == 0) {
            addedge(edges[i][0], edges[i][1]);
        }
    }

    vector<int> res;
    for(int i = q - 1; i >= 0; i--) {
        if(queries[i][0] == 1) {
            int edgeidx = queries[i][1] - 1;
            addedge(edges[edgeidx][0], edges[edgeidx][1]);
        } else {
            res.push_back(cnts[queries[i][1] - 1]);
        }
    }

    reverse(res.begin(), res.end());

    for(int r : res) {
        cout << r << '\n';
    }

    return 0;
}