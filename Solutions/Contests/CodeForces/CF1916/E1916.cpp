#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll ans = 0;

void tree_dp(int i, vector<vector<int>> &adj, vector<ll> &activities, vector<ll> &dp) {
    vector<ll> children;
    
    for(auto child : adj[i]) {
        tree_dp(child, adj, activities, dp);
        children.push_back(dp[child]);
    }
    sort(children.begin(), children.end());

    if(children.size() >= 2) {
        ans = max(ans, (children[children.size() - 1] + activities[i]) * (children[children.size() - 2] + activities[i]));
    }
    if(children.size() >= 1) {
        ans = max(ans, (children[children.size() - 1] + activities[i]) * activities[i]);
    }
    
}

void solve() {
    int n; cin >> n;

    vector<vector<int>> adj(n);

    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        adj[i].push_back(p);
        // adj[p].push_back(i);
    }

    vector<ll> activities(n);
    for(auto &x : activities) cin >> x;

    vector<ll> dp(n);
    ans = 0;

    tree_dp(0,adj,activities,dp);

    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}