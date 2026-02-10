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
    
    int n, m; cin >> n >> m;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        a[u] = max(a[u], v);
    }

    // cout << "a : " << a << endl;

    vector<vector<int>> ch(n);
    for(int i = 0; i + 1 < n; i++) {
        ch[a[i]].push_back(i);
    }

    vector<vector<int>> dp(n);
    ll res = 0;

    auto dfs = [&](auto self, int i) -> void {
        int mc = -1;
        for(int c : ch[i]) {
            self(self, c);
            if(mc == -1 || dp[c].size() > dp[mc].size()) {
                mc = c;
            }
        }

        if(mc != -1) swap(dp[mc], dp[i]);

        for(int c : ch[i]) {
            if(c != mc) {
                int prev_here = 0;
                int prev_there = (dp[i].size() > dp[c].size() ? dp[i][dp[i].size() - dp[c].size() - 1] : 0);
                for(int j = 0; j < dp[c].size(); j++) {
                    res += 1LL * (dp[c].size() - j) * (1LL * (dp[c][j] - prev_here) * (dp[i][dp[i].size() - dp[c].size() + j]) + 1LL * (dp[i][dp[i].size() - dp[c].size() + j] - prev_there) * dp[c][j]);
                    prev_here = dp[c][j];
                    prev_there = dp[i][dp[i].size() - dp[c].size() + j];
                    dp[i][dp[i].size() - dp[c].size() + j] += dp[c][j];
                }
            }
        }

        int prev = dp[i].size() ? dp[i].back() : 0;
        dp[i].push_back(prev + 1);

        // cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
    };

    dfs(dfs, n - 1);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}