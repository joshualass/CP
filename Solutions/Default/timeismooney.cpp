//http://www.usaco.org/index.php?page=viewproblem2&cpid=993
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll dp[2001][1001];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    freopen("time.in","r",stdin);
    freopen("time.out","w",stdout);

    ll n, m, C; cin >> n >> m >> C;
    vector<ll> v(n);
    for(auto &x: v) cin >> x;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
    }

    for(int i = 0; i <= 1000; i++) {
        if(i) {
            fill(begin(dp[i]),begin(dp[i])+1001,-1);
        } else {
            fill(begin(dp[i]),begin(dp[i])+1001,-1);
        }
    }
    dp[0][0] = 0;
    ll most = 0;
    for(int r = 0; r < 2001; r++) {
        for(int c = 0; c < n; c++) {
            if(r != 2000) {
                if(dp[r][c] != -1) {
                    for(auto x : adj[c]) {
                        dp[r+1][x] = max(dp[r+1][x],dp[r][c] + v[c]);
                    }
                }
            } 
            if(c == 0) {
                if(r < 10) {
                    // cout << "r: " << r << " " << dp[r][c] - C * r * r << "\n";
                }
                most = max(most, dp[r][c] - C * r * r);
            }
        }
    }

    cout << most << "\n";

    return 0;
}