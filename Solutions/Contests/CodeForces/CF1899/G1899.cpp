#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n, q; cin >> n >> q;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> p(n), rp(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
        rp[p[i]] = i;
    }

    vector<vector<array<int,3>>> queries(n);
    for(int qq = 0; qq < q; qq++) {
        int l, r, x; cin >> l >> r >> x;
        l--;
        x--;
        queries[x].push_back({l, r, qq});
    }

    vector<int> res(q);

    vector<set<int>> s(n);

    auto dfs = [&](auto self, int i, int p) -> void {
        s[i].insert(rp[i]);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                if(sz(s[c]) > sz(s[i])) {
                    swap(s[c], s[i]);
                }
            }
        }
        for(int c : adj[i]) {
            if(c != p) {
                for(int x : s[c]) s[i].insert(x);
            }
        }
        for(auto [l, r, id] : queries[i]) {
            auto it = s[i].lower_bound(l);
            res[id] = it != s[i].end() && *it < r;
        }
    };

    dfs(dfs, 0, -1);
    for(int x : res) cout << (x ? "YES" : "NO") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
        if(i + 1 < casi) cout << '\n';
    }

    return 0;
}