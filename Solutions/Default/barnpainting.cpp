// http://www.usaco.org/index.php?page=viewproblem2&cpid=766
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void tree_dp(int i, int p, vector<vector<int>> &adj, vector<int> &forced, vector<array<ll,3>> &dp) {

    array<ll,3> ans{1,1,1};

    for(auto node : adj[i]) {
        if(node != p) {
            tree_dp(node, i, adj, forced, dp);
            ans[0] *= (dp[node][1] + dp[node][2]);
            ans[0] %= MOD;
            ans[1] *= (dp[node][0] + dp[node][2]);
            ans[1] %= MOD;
            ans[2] *= (dp[node][1] + dp[node][0]);
            ans[2] %= MOD;
        }
    }
    if(forced[i] != -1) {
        for(int j = 0; j < 3; j++) {
            if(forced[i] != j) {
                ans[j] = 0;
            }
        }
    }
    dp[i] = ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("barnpainting.in","r",stdin);
    freopen("barnpainting.out","w",stdout);   

    int n, k; cin >> n >> k;

    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> forced(n,-1);
    
    for(int i = 0; i < k; i++) {
        int b, c; cin >> b >> c;
        b--; c--;
        forced[b] = c;
    }

    vector<array<ll,3>> dp(n);

    tree_dp(0, -1, adj, forced, dp);

    cout << (dp[0][0] + dp[0][1] + dp[0][2]) % MOD << '\n';

    return 0;
}