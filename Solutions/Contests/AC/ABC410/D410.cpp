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
        int a, b, w; cin >> a >> b >> w;
        a--; b--;
        adj[a].push_back({b, w});
        // adj[b].push_back({a, w});
    }

    vector<vector<int>> vis(n, vector<int>(1 << 10));
    queue<array<int,2>> q;

    auto add_q = [&](int i, int j) -> void {
        if(vis[i][j] == 0) {
            vis[i][j] = 1;
            q.push({i, j});
        }
    };

    add_q(0, 0);

    while(q.size()) {
        auto [i, j] = q.front();
        q.pop();

        for(auto [c, w] : adj[i]) {
            add_q(c, j ^ w);
        }

    }

    for(int i = 0; i < 1 << 10; i++) if(vis.back()[i]) {
        cout << i << '\n';
        return 0;
    }

    cout << "-1\n";

    return 0;
}
