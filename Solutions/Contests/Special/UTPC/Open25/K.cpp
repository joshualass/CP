#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    auto get_better = [&](array<int,2> a, array<int,2> b, int d) -> array<int,2> {
        if(d & 1) {
            if(a[1] > b[1]) {
                return a;
            } else if(a[1] < b[1]) {
                return b;
            } else if(a[0] > b[0]) {
                return a;
            } else {
                return b;
            }
        } else {
            if(a[0] > b[0]) {
                return a;
            } else if(a[0] < b[0]) {
                return b;
            } else if(a[1] > b[1]) {
                return a;
            } else {
                return b;
            }
        }
    };

    auto dfs = [&](auto self, int i, int p, int depth) -> array<int,2> {
        array<int,2> best = {0,0};
        for(int c : adj[i]) {
            if(c != p) {
                best = get_better(best, self(self, c, i, depth + 1), depth);
            }
        }

        for(int j = 0; j < 2; j++) {
            best[j] += a[i][j];
        }
        return best;
    };

    array<int,2> res = dfs(dfs, 0, -1, 0);

    cout << res[0] << " " << res[1] << '\n';

    return 0;
}
