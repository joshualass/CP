#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;

    vector<vector<pair<int,ll>>> adj(n), trans(n);

    for(int i = 0; i < m; i++) {
        ll u, v, w; cin >> u >> v >> w;
        u--; v--;
        adj[u].push_back({v,w});
        trans[v].push_back({u,w});
    }

    priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>> pq; //time, node, 0/1 - node 1 can reach ... can we use adj or just trans.
    vector<vector<ll>> times(2,vector<ll>(n,-1));
    pq.push({0,0,1});
    while(pq.size()) {
        array<ll,3> p = pq.top();
        pq.pop();

        auto [time, i, reach] = p;

        if(times[reach][i] == -1) {
            times[reach][i] = time;
            for(pair<int,ll> p : trans[i]) {
                if(times[0][p.first] == -1) {
                    pq.push({time + p.second, p.first, 0});
                }
            }
            if(reach) {
                for(pair<int,ll> p : adj[i]) {
                    if(times[1][p.first] == -1) {
                        pq.push({time + p.second, p.first, 1});
                    }
                }
            }
        }
    }

    for(int i = 1; i < n; i++) {
        if(times[0][i] == -1 || times[1][i] == -1) {
            cout << max(times[0][i], times[1][i]) << " \n"[i == n - 1];
        } else {
            cout << min(times[0][i], times[1][i]) << " \n"[i == n - 1];
        }
    }

    return 0;
}