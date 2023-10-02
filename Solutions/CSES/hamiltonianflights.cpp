#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<vector<int>> nums(n);
    for(int i = 0; i < (1 << n) - 1; i++) {
        nums[__builtin_popcount(i)].push_back(i);
    }
    vector<vector<int>> dp(n,vector<int>(1 << n));
    dp[0][1] = 1;
    for(int i = 0; i < m; i++) {
        int a, b;cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    for(int i = 0; i < n; i++) { //total number of cities visited
        for(int j = 0; j < n; j++) { // starting at node j
            for(auto x : nums[i]) { //every starting state 
                if(((x >> j) & 1) == 0 || dp[j][x] == 0) continue;//can't do this state if we have not visited the current city. the dp will be 0.
                for(auto y : adj[j]) {
                    if((x & (1 << y)) == 0) {
                        dp[y][x | (1 << y)] += dp[j][x];
                        if(dp[y][x | (1 << y)] >= MOD) dp[y][x | (1 << y)] -= MOD;
                    }
                }
            }
        }
    }
    cout << dp[n-1][(1 << n) - 1] << "\n";
    return 0;
}