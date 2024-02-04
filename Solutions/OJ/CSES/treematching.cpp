#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void tree_matching(int i, int p, vector<vector<int>> &adj, vector<pair<int,int>> &dp) {

    int sum_including = 0;
    bool found = 0;
    for(auto node : adj[i]) {
        if(node != p) {
            tree_matching(node, i, adj, dp);
            sum_including += dp[node].first;
            if(dp[node].second >= dp[node].first) {
                found = 1;
            }
        }
    }
    dp[i] = {sum_including + found, sum_including};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<pair<int,int>> dp(n,{-1,-1});

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    tree_matching(0,-1,adj,dp);
    cout << dp[0].first << '\n';

    return 0;
}