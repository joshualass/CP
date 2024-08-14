#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m; cin >> n >> m;
    ll t0, t1, t2; cin >> t0 >> t1 >> t2;
    vector<vector<array<ll,3>>> adj(n);
    for(int i = 0; i < m; i++) {
        ll u, v, l1, l2; cin >> u >> v >> l1 >> l2;
        u--; v--;
        adj[u].push_back({v,l1,l2});
        adj[v].push_back({u,l1,l2});
    }

    auto poss = [&](ll s) -> bool {
        vector<ll> vis(n,-1);
        priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
        pq.push({s,0});
        while(pq.size()) {
            auto [time, i] = pq.top();
            pq.pop();
            if(vis[i] != -1) continue;
            vis[i] = time;
            for(auto [c, l1, l2] : adj[i]) {
                if(vis[c] == -1) {
                    ll bustime = time + l1;
                    if(time < t2 && time + l1 > t1) {
                        bustime = t2 + l1;
                    }
                    pq.push({min(bustime, time + l2), c});
                }
            }
        }
        return vis[n - 1] <= t0;
    };

    ll lo = -1, hi = t0;
    while(lo != hi) {
        ll m = (lo + hi + 1) / 2;
        if(poss(m)) {
            lo = m;
        } else {
            hi = m - 1;
        }
    }
    cout << lo << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}