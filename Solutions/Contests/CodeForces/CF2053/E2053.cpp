#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> p(n), cnt(n), no_nei_leaf(n,1);
    int leafcnt = 0;
    auto dfs = [&](auto self, int i, int par) -> void {
        p[i] = par;
        if(adj[i].size() == 1) {
            leafcnt++;
            no_nei_leaf[i] = 0;
        } else {
            for(int c : adj[i]) {
                if(adj[c].size() == 1) {
                    no_nei_leaf[i] = 0;
                }
            }
        }
        cnt[i] += no_nei_leaf[i];
        for(int c : adj[i]) {
            if(c != par) {
                self(self, c, i);
                cnt[i] += cnt[c];
            }
        }
    };
    dfs(dfs, 0, -1);
    ll res = 1LL * leafcnt * (n - leafcnt);
    // cout << "start res : " << res << '\n';
    for(int i = 0; i < n; i++) {
        if(adj[i].size() != 1) {
            int x = 0;
            for(int c : adj[i]) {
                if(no_nei_leaf[c] == 0) {
                    if(c == p[i]) {
                        res += cnt[0] - cnt[i];
                        x += cnt[0] - cnt[i];
                    } else {
                        res += cnt[c];
                        x += cnt[c];
                    }
                }
            }
            // cout << "i : " << i << " i contrib : " << x << '\n';
        }
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}