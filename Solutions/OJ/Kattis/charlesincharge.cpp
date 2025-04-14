#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k; cin >> n >> m >> k;
    vector<vector<array<ll,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    auto getsp = [&](ll m) -> ll {
        priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
        pq.push({0,0});
        vector<ll> vis(n, 1e18);
        // cout << "ttfang m : " << m << '\n';
        while(pq.size()) {
            auto [dis, i] = pq.top();
            pq.pop();
            if(vis[i] != 1e18) continue;
            vis[i] = dis;
            for(auto [to, w] : adj[i]) {
                // cout << "try push : " << dis + w << ", " << to << '\n';
                if(vis[to] == 1e18 && w <= m) {
                    pq.push({dis + w, to});
                    // cout << "push : " << dis + w << ", " << to << '\n';
                }
            }
        }
        // cout << "m : " << m << " last : " << vis[n-1] << '\n';
        // cout << "m : " << m << " vis : " << vis << '\n';
        return vis[n-1];
    };

    ll sp = getsp(1e18);

    ll l = 1, r = 1e9;
    while(l != r) {
        ll m = (l + r) / 2;
        if(sp * (100 + k) >= getsp(m) * 100) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    
    cout << l << '\n';

    return 0;
}
