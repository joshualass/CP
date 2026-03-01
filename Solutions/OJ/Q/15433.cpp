#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef long long ll;
typedef long double ld;
typedef vector<ll> vl;
typedef pair<ll, ll> pll;
#define sz(x) (int) (x).size()

/*
1
8
1 2 10
2 3 10
3 4 1
2 5 10
5 6 1
2 7 10
7 8 1

1  
6
1 2 0
2 3 10
1 6 0
6 4 0
4 5 10

1  
6
1 2 0
2 3 10
1 6 0
6 4 10
4 5 0

1  
6
1 2 0
2 3 10
1 6 0
6 4 10
4 5 0
40 30 20 20 20 10 10 10 0 0 0

1
6
1 2 0
2 3 10
1 6 0
6 4 0
4 5 10
40 30 20 20 20 20 20 10 0 0 0
PS C:\Users\andwe\Downloads\contest12> .\B.exe
1
6
1 2 0
2 3 10
1 6 0
6 4 0
4 5 10
40 30 20 20 20 20 20 10 0 0 0
PS C:\Users\andwe\Downloads\contest12> .\B.exe
1
6
1 2 0
2 3 10
1 6 0
6 4 0
4 5 10
40 30 20 20 20 20 10 0 0 0 0
*/

void solve() {

    int n; cin >> n;
    ll tc = 0;
    vector<vector<array<ll,2>>> adj(n);
    
    for(int i = 1; i < n; i++) {
        int u, v, c; cin >> u >> v >> c;
        u--; v--;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
        tc += c * 2;
    }

    vector<vector<ll>> dp(n);
    vector<ll> res(2 * n - 1);

    auto dfs = [&](auto self, int i, int p) -> void {

        for(auto [c, w] : adj[i]) {
            if(c != p) {
                self(self, c, i);
                for(ll &x : dp[c]) x += w;
                dp[c].insert(dp[c].begin(), 0);
                dp[c].push_back(dp[c].back() + w);
            }
        }

        sort(adj[i].begin(), adj[i].end(), [&](const auto &lhs, const auto &rhs) -> bool {
            return sz(dp[lhs[0]]) < sz(dp[rhs[0]]);
        });

        vector<vector<ll>> dp_here(3, vector<ll>(1));
        for(auto [c, w] : adj[i]) {
            if(c != p) {
                int prev_size = sz(dp_here[0]) - 1;
                int add_size = sz(dp[c]) - 1;
                for(int j = 0; j < 3; j++) {
                    for(int k = 0; k < add_size; k++) {
                        dp_here[j].push_back(0);
                    }
                }

                for(int j = 2; j >= 0; j--) {
                    for(int k = prev_size; k >= 0; k--) {
                        dp_here[j][k + add_size] = max(dp_here[j][k + add_size], dp_here[j][k] + dp[c][add_size]);
                        if(j + 1 < 3) {
                            for(int len = 0; len <= add_size; len++) {
                                dp_here[j + 1][k + len] = max(dp_here[j + 1][k + len], dp_here[j][k] + dp[c][len]);
                            }
                        }
                    }
                }
            }
        }

        // cout << "i : " << i << endl;

        for(int j = 0; j < sz(dp_here[0]); j++) {
            ll v = 0;
            for(int k = 0; k < 3; k++) v = max(v, dp_here[k][j]);
            res[j] = max(res[j], v);
            dp[i].push_back(v);
            // cout << v << " ";
        }
        // cout << endl;
    };

    dfs(dfs, 0, -1);
    for(int i = 0; i < 2 * n - 1; i++) cout << tc - res[i] << " \n"[i == 2 * n - 2];

}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

    int t; cin >> t;
    while(t-->0) solve();

    return 0;
}