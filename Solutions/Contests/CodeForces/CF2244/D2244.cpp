#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll inf = 1e18;

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<array<ll,2>> dp(n + 1);

    dp[n][1] = -inf;
    vector<int> vis(n);
    for(int i = 0; i < m; i++) {
        int b; cin >> b;
        b--;
        vis[b] = 1;
    }

    for(int i = n - 1; i >= 0; i--) {
        dp[i][0] = dp[i+1][0] + a[i];
        dp[i][1] = dp[i+1][1] - a[i];
        if(vis[i]) {
            dp[i][0] = max(dp[i][0], dp[i+1][1] + a[i]);
            dp[i][1] = max(dp[i][1], dp[i+1][0] - a[i]);
        }
    }

    cout << max(dp[0][0], dp[0][1]) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}