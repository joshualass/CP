#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

array<int,2> operator+(const array<int,2> &lhs, const array<int,2> &rhs) {
    return {lhs[0] + rhs[0], lhs[1] + rhs[1]};
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

    //every edge needs to be colored!
    vector<array<array<int,2>,2>> dp(n); // index, {coloring rootnode, coloring subtree}, {0/1} depending on whether this state is possible with leaf-root.

    auto dfs = [&](auto self, int i, int p) -> void {

        array<int,2> color = {0,0};
        array<int,2> nocolor = {0,0};

        for(int c : adj[i]) {
            if(c != p) {
                
                self(self,c,i);

                if(dp[c][0][0] < dp[c][1][0] || dp[c][0][0] == dp[c][1][0] && dp[c][0][1] > dp[c][1][1]) {
                    color = color + dp[c][0];
                } else {
                    color = color + dp[c][1];
                }

                nocolor = nocolor + dp[c][0];

                if(adj[c].size() == 1) {
                    nocolor[1]++;
                }

            }
        }
        color[0]++;
        dp[i] = {color, nocolor};

    };

    dfs(dfs,0,-1);

    // cout << "dp : " << dp << '\n';

    int res = min(dp[0][0][0] - (dp[0][0][1] ? 1 : 0), dp[0][1][0] - (dp[0][1][1] ? 1 : 0));

    if(adj[0].size() == 1) {
        int c = adj[0][0];
        res = min({res, dp[c][0][0], dp[c][1][0]});
    }

    cout << n - res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}