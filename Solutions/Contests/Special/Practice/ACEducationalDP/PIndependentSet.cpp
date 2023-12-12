#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//tree DP

void tree_dp(int i, int p, vector<pair<ll,ll>> &dp, vector<vector<int>> &adj) {
    ll white = 1;
    ll black = 1;

    for(auto node : adj[i]) {
        if(node != p) {
            tree_dp(node, i, dp, adj);
            white *= dp[node].first + dp[node].second;
            white %= MOD;
            black *= dp[node].first;
            black %= MOD;
        }
    }
    // cout << "i : " << i << " white : " << white << " black : " << black << '\n';
    dp[i] = {white, black};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; 
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    //how many ways to color this subtree if this node is colored white/black
    vector<pair<ll,ll>> dp(n);

    tree_dp(0,-1, dp, adj);

    cout << (dp[0].first + dp[0].second) % MOD << '\n';

    return 0;
}