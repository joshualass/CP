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
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
    }

    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq;
    vector<vector<int>> vis(n, vector<int>(2));
    vector<vector<ll>> dist(n, vector<ll>(2, 1e18));

    auto add_q = [&](int i, int j, ll d) -> void {
        if(vis[i][j] || d >= dist[i][j]) return;
        dist[i][j] = d;
        pq.push({d, i, j});
    };

    add_q(0, 0, 0);

    while(pq.size()) {
        auto [d, i, j] = pq.top();
        pq.pop();
        if(vis[i][j]) continue;
        vis[i][j] = 1;

        for(auto [to, w] : adj[i]) {
            add_q(to, j, w + dist[i][j]);
            if(j == 0) add_q(to, 1, (w / 2) + dist[i][j]);
        }

    }

    cout << dist[n-1][1] << '\n';

    return 0;
}
