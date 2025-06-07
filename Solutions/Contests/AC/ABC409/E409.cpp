#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<array<ll,2>>> adj(n);
    for(int i = 1; i < n; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    ll res = 0;

    auto dfs = [&](auto self, int i, int p) -> void {

        for(auto [c, w] : adj[i]) {
            if(c != p) {
                self(self, c, i);
                res += abs(a[c]) * w;
                a[i] += a[c];
            }
        }

    };

    dfs(dfs, 0, -1);

    cout << res << '\n';

    return 0;
}
