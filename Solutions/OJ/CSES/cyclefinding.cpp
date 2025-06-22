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

    vector<ll> dist(n);
    vector<int> par(n, -1);

    auto relax = [&]() -> int {
        int x = -1;
        for(int i = 0; i < n; i++) {
            for(auto [to, w] : adj[i]) {
                if(dist[i] + w < dist[to]) {
                    dist[to] = dist[i] + w;
                    par[to] = i;
                    x = to;
                }
            }
        }
        return x;
    };

    for(int i = 0; i < n; i++) relax();

    int p = relax();
    if(p == -1) {
        cout << "NO\n";
    } else {
        vector<int> cycle;
        vector<int> vis(n);
        while(1) {
            if(vis[p]) break;
            vis[p] = 1;
            cycle.push_back(p);
            p = par[p];
        }
        reverse(cycle.begin(), cycle.end());
        while(cycle.back() != p) cycle.pop_back();
        cycle.insert(cycle.begin(), p);
        cout << "YES\n";
        for(int i = 0; i < cycle.size(); i++) cout << cycle[i] + 1 << " \n"[i == cycle.size() - 1];
    }

    return 0;
}
