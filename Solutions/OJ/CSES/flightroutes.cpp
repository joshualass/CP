#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<vector<array<int,2>>> adj(n);

    for(int i = 0; i < m; i++) {
        int a, b, c; cin >> a >> b >> c;
        a--; b--;
        adj[a].push_back({b, c});
    }

    vector<vector<ll>> vis(n);
    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;

    auto add_q = [&](int i, ll d) -> void {
        if(vis[i].size() < k) pq.push({d, i});
    };

    add_q(0, 0);
    while(pq.size()) {
        auto [d, i] = pq.top();
        pq.pop();
        if(vis[i].size() == k) continue;
        vis[i].push_back(d);
        for(auto [to, w] : adj[i]) add_q(to, d + w);
    }

    for(int i = 0; i < k; i++) cout << vis[n - 1][i] << " \n"[i == k - 1];

    return 0;
}
