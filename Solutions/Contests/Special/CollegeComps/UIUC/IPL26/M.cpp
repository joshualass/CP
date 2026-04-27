#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

void solve() {
    
    int n; cin >> n;
    vector<int> t;
    vector<array<int,2>> a(n);

    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
            t.push_back(y);
        }
    }

    eraseduplicates(t);
    int m = sz(t);
    vector<vector<array<int,2>>> adj(m);

    for(int i = 0; i < n; i++) {
        auto [u, v] = a[i];
        u = lower_bound(t.begin(), t.end(), u) - t.begin();
        v = lower_bound(t.begin(), t.end(), v) - t.begin();
        // cout << "i : " << i << " u : " << u << " v : " << v << endl;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
    }

    vector<array<int,2>> res;
    vector<int> vis(m), vise(n);

    auto merge = [&](int &c, int nx) -> void {
        if(nx == -1) return;
        if(c == -1) {
            c = nx;
        } else {
            res.push_back({c, nx});
            c = -1;
        }
    };

    auto dfs = [&](auto self, int i, int p_idx) -> int {
        assert(vis[i] == 0);
        vis[i] = 1;

        int cur = -1;
        for(auto [c, idx] : adj[i]) {
            if(vise[idx] == 0) {
                vise[idx] = 1;
                if(vis[c] == 0) {
                    merge(cur, self(self, c, idx));
                } else {
                    merge(cur, idx);
                }
            }
        }

        if(cur == -1) {
            return p_idx;
        } else {
            merge(cur, p_idx);
            return -1;
        }

    };

    for(int i = 0; i < m; i++) {
        if(vis[i] == 0) {
            // cout << "vis i : " << i << endl;
            dfs(dfs, i, -1);
        }
    }

    cout << sz(res) << '\n';
    for(auto x : res) {
        cout << x[0] + 1 << " " << x[1] + 1 << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}