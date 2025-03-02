#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n, s, t; cin >> n >> s >> t;
    s--; t--;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> dists(n,0);
    vector<int> par(n, -1);

    auto dfs = [&](auto self, int i, int p, int d) -> void {
        dists[i] = d;
        par[i] = p;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, d + 1);
            }
        }
    };

    dfs(dfs, t,-1, 0);

    vector<int> res, vis(n);
    int furthest = 0;
    for(int i = 0; i < n; i++) {
        if(dists[i] > dists[furthest]) {
            furthest = i;
        }
    }

    // cout << "par : " << par << '\n';
    // cout << "dists : " << dists << '\n';
    // cout << "furthest_idx : " << furthest << '\n';

    while(furthest != -1) {
        res.push_back(furthest);
        vis[furthest] = 1;
        furthest = par[furthest];
    }


    reverse(res.begin(), res.end());
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) res.push_back(i);
    }
    reverse(res.begin(), res.end());
    for(int i = 0; i < n; i++) {
        cout << res[i] + 1 << " \n"[i == n - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}