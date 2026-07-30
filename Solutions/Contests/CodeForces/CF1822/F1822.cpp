#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll n, k, cost; cin >> n >> k >> cost;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<ll> dp(n);

    auto dfs0 = [&](auto self, int i, int p) -> void {
        ll res = 1;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
                res = max(res, dp[c] + 1);
            }
        }
        dp[i] = res;
    };

    ll res = 0;
    auto dfs1 = [&](auto self, int i, int p, int rd) -> void {
        vector<array<ll,2>> e;
        
        for(int c : adj[i]) {
            e.push_back({dp[c], c});
            res = max(res, dp[c] * k - cost * rd);
        }
        // cout << "i : " << i << " rd : " << rd << " e : " << e << endl;
        sort(e.begin(), e.end());
        for(int c : adj[i]) {
            if(c != p) {
                dp[i] = 1;
                for(int j = sz(e) - 1; j >= 0; j--) {
                    if(e[j][1] != c) {
                        dp[i] = max(dp[i], e[j][0] + 1);
                        break;
                    }
                }
                self(self, c, i, rd + 1);
            }
        }
    };

    dfs0(dfs0, 0, -1);
    // cout << "dp : " << dp << endl;
    dfs1(dfs1, 0, -1, 0);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}