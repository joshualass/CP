#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<vector<int>> vis(n, vector<int>(k, -1));
    vector<vector<int>> dists(n, vector<int>(k, -1));
    queue<array<int,5>> q;

    auto add_q = [&](int i, int d, int dist, int par) -> void {
        if(vis[i][d] == -2) return;
        if(vis[i][d] == -1) {
            dists[i][d] = dist;
            q.push({i, d, dist, par, 0});
            vis[i][d] = par;
        } else {
            q.push({i, d, dist, vis[i][d], 1});
            dists[i][d] = dist;
            vis[i][d] = -2;
        }
    };

    add_q(0, 0, 0, -2);

    while(q.size()) {
        auto [i, d, dist, par, single_mode] = q.front();
        q.pop();

        int nx_d = (d + k - 1) % k;
        int nx_p = ((d + k - 1) % k == 0 ? -2 : i);
        int nx_dist = dist + ((d + k - 1) % k == 0);

        // cout << "i : " << i << " d : " << d << " dist : " << dist << " par : " << par << " single_mode : " << single_mode << '\n';
        // cout << "nx_d : " << nx_d << " nx_p : " << nx_p << " nx_dist : " << nx_dist << '\n';

        if(single_mode) {
            add_q(par, nx_d, nx_dist, nx_p);
        } else {
            for(int c : adj[i]) {
                if(c != par) {
                    add_q(c, nx_d, nx_dist, nx_p);
                }
            }
        }

    }

    for(int i = 1; i < n; i++) {
        cout << dists[i][0] << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}