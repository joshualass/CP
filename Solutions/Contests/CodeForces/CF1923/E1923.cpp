#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void tree_dp(int i, int p, vector<int> &colors, vector<vector<int>> &adj, vector<ll> &color_dp, ll &ans) {
    int curr_colorval = color_dp[colors[i]];
    for(int child : adj[i]) {
        if(child != p) {
            color_dp[colors[i]] = 0;
            tree_dp(child,i,colors,adj,color_dp,ans);
            // cout << "i : " << i << " child : " << child << " add score : " << color_dp[colors[i]] * (color_dp[colors[i]] + 1) / 2 << '\n';
            ans += color_dp[colors[i]] * (color_dp[colors[i]] + 1) / 2;
        }
    }
    color_dp[colors[i]] = curr_colorval + 1;
}

void solve() {
    int n; cin >> n;
    vector<int> colors(n);
    for(int &x : colors) {
        cin >> x;
        x--;
    }
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<ll> color_dp(n);
    ll ans = 0;
    tree_dp(0,-1,colors,adj,color_dp,ans);
    for(ll colorz : color_dp) {
        ans += colorz * (colorz-1) / 2;
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}