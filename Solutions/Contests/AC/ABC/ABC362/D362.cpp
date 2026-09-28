#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> res(n,-1);
    vector<vector<array<ll,2>>> adj(n);
    for(int i = 0; i < m; i++) {
        ll u, v, b; cin >> u >> v >> b;
        u--; v--;
        adj[u].push_back({v,b});
        adj[v].push_back({u,b});

    }

    priority_queue<array<ll,2>, vector<array<ll,2>>, greater<array<ll,2>>> pq;
    pq.push({a[0], 0});
    while(pq.size()) {

        array<ll,2> c = pq.top();
        pq.pop();
        if(res[c[1]] != -1) continue;
        res[c[1]] = c[0];

        for(array<ll,2> to : adj[c[1]]) {
            if(res[to[0]] == -1) {
                pq.push({c[0] + to[1] + a[to[0]], to[0]});
            }
        }
    }

    for(int i = 1; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }
    

    return 0;
}