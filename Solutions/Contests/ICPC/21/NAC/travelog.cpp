#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
2 2 0
1 2 1
1 2 1


*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, k; cin >> n >> m >> k;
    // cout << "n : " << n << " m : " << m << " k : " << k << endl;
    vector<vector<array<ll,2>>> adj(n);
    // vector<map<ll,ll>> adj(n);
    for(int i = 0; i < m; i++) {
        ll u, v, h; cin >> u >> v >> h;
        u--; v--;
        // if(adj[u].count(v)) {
            // adj[u][v] = min(adj[u][v], h);
        // } else {
            // adj[u][v] = h;
        // }
        adj[u].push_back({v, h});
    }

    vector<ll> t(k);
    for(ll &x : t) cin >> x;

    priority_queue<array<ll,4>, vector<array<ll,4>>, greater<array<ll,4>>> pq;
    vector<ll> vis(n,-1);
    vector<vector<int>> p(n);

    pq.push({0, 0, -1, 0});
    while(pq.size()) {
        auto [dist, i, par, ti] = pq.top();
        pq.pop();
        // cout << "dist : " << dist << " i : " << i << " par : " << par << " ti : " << ti << endl;
        if(ti < k && dist > t[ti]) continue;
        if(ti < k && dist == t[ti]) ti++;
        if(vis[i] != -1) {
            if(dist == vis[i]) p[i].push_back(par);
            continue;
        }
        vis[i] = dist;
        p[i].push_back(par);
        for(auto [to, w] : adj[i]) {
            pq.push({dist + w, to, i, ti});
        }
    }

    // cout << "vis : " << vis << '\n';
    // for(int i = 0; i < n; i++) {
    //     cout << "par[i] : " << p[i] << '\n';
    // }

    if(k && vis.back() < t.back() || vis.back() == -1) {
        cout << "0\n";
        return 0;
    }

    vector<int> path;
    int many = 0;

    auto dfs = [&](auto self, int i) -> void {
        // cout << "i : " << i << '\n';
        if(i == -1) return;
        if(p[i].size() > 1 || p[i].empty()) {
            many = 1;
            return;
        }

        path.push_back(i);
        self(self, p[i][0]);

    };

    dfs(dfs, n - 1);

    if(many) {
        cout << "1\n";
    } else {
        cout << path.size() << '\n';
        reverse(path.begin(), path.end());
        for(int i = 0; i < path.size(); i++) {
            cout << path[i] + 1 << "\n";
        }
    }

    return 0;
}
