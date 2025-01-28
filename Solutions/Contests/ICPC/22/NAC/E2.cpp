#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }   
    const int G = 2000;
    vector<vector<int>> h(G + 1);
    vector<int> bad(G + 1);
    for(int i = 1; i <= G; i++) {
        for(int j = 2; j <= G; j++) {
            if(gcd(i,j) != 1) h[i].push_back(j);
            if(i % j == 0 && (i / j) % j == 0) {
                bad[i] = 1;
            }
        }
    }

    for(int i = 1; i <= G; i++) {
        if(bad[i]) {
            cout << "bad i : " << i << '\n';
        }
    }

    auto dfs = [&](auto self, int i, int p) -> vector<int> {
        vector<int> dp(max(201, min(G + 1, ((int) (sqrt(adj[i].size()) * 20)) + 1)));
        iota(dp.begin(), dp.end(), 0);
        dp[a[i]] = 0;
        for(int c : adj[i]) {
            if(c != p) {
                vector<int> b = self(self, c, i);
                for(int j = 2; j < dp.size(); j++) {
                    assert(j <= G);
                    if(j <= 200 || !bad[j]) {
                        int lo = 1e9;
                        for(int g : h[j]) {
                            if(g < b.size()) {
                                lo = min(lo, b[g]);
                            }
                        }
                        dp[j] = min((int) 1e9, dp[j] + lo);
                    }
                }
            }
        }
        return dp;
    };

    vector<int> res = dfs(dfs, 0, -1);

    int ans = 1e9;
    for(int i = 2; i < res.size(); i++) {
        if(i <= 100 || !bad[i]) ans = min(ans, res[i]);
    }
    cout << ans << '\n';

    return 0;
}