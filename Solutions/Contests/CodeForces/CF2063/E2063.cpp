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
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ll res = 0;

    //prefix sum only

    //doing things 1-indexed, [l, r) ._.
    auto get = [](vector<ll> &a, int l, int r) -> ll {
        assert(r <= a.size() && l >= 1 && l <= r);
        return  a[a.size() - l] - a[a.size() - r];
    };

    auto add_merge = [&](vector<ll> &lhs, vector<ll> &rhs) -> void {
        // cout << "lhs : " << lhs << " rhs : " << rhs << '\n';
        if(rhs.size() > lhs.size()) {
            swap(lhs, rhs);
        }

        for(int i = 1; i < rhs.size(); i++) {
            res += (i * 2 - 1) * get(rhs, i, i + 1) * get(lhs, i, lhs.size());
        }

        for(int i = 1; i + 1 < rhs.size(); i++) {
            res += (i * 2 - 1) * get(lhs, i, i + 1) * get(rhs, i + 1, rhs.size());
        }

        for(int i = 1; i < rhs.size(); i++) {
            lhs[lhs.size() - rhs.size() + i] += rhs[i];
        }

        // cout << "res lhs : " << lhs << '\n';

    };

    vector<vector<ll>> dp(n, vector<ll>(1, 0));

    auto dfs = [&](auto self, int i, int p) -> void {
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                // cout << "i : " << i << " c : " << c << '\n';
                add_merge(dp[i], dp[c]);
            }
        }
        dp[i].push_back(dp[i].back() + 1);
    };

    dfs(dfs, 0, -1);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}