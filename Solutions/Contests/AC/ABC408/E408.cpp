#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;

    vector<vector<array<int,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto check = [&](int bm) -> int {
        queue<int> q;
        vector<int> vis(n);
        auto addq = [&](int idx) -> void {
            if(vis[idx]) return;
            vis[idx] = 1;
            q.push(idx);
        };

        addq(0);

        while(q.size()) {
            int idx = q.front();
            q.pop();
            for(auto [to, w] : adj[idx]) {
                if((w | bm) == bm) {
                    addq(to);
                }
            }
        }

        return vis[n - 1];

    };

    int res = (1 << 30) - 1;
    for(int i = 29; i >= 0; i--) {
        if(check(res - (1 << i))) res -= 1 << i;
    }

    cout << res << '\n';

    return 0;
}
