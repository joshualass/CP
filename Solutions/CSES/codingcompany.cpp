// https://cses.fi/problemset/task/1665
/*key insight: the complexity is too large without optimization (n^3 * x)
we are able to do this by having less knapsack states (n * x) vs. (n * n * x)
and then iterate over the n * x states with each of the n elements
we store less data as well as know that for each state that it's optimal 
we need to pay close attention to the order of the elements that we knapsack
and make sure to do them in sorted earlier, so we are able to use the method which has 
a factor of n less states

store - current score, current low score on team
we are able to do it this way becuase we are iterating over the elements in sorted order (lowest to highest)

for each coder, 
iterate in order of decreasing current score, and then by decreasing low team score 
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dp[5001][101]; 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;

    vector<int> coders(n);

    for(auto &x: coders) cin >> x;

    sort(coders.begin(), coders.end());
    for(int i = 0; i < 5001; i++)  {
        memset(dp[i], 0, sizeof(dp[i]));
    }
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) { //iterate over each coder starting with lowest coder 
        int coder = coders[i];
        for(int currscore = x; currscore >= 0; currscore--) {
            for(int teamlo = coder; teamlo >= 0; teamlo--) { //don't need to iterate over every extra state
                //coder score will always be greater than teamlo
                //add to current team
                int add = dp[currscore][teamlo];
                dp[currscore][teamlo] = 0;
                {
                    int nextcurrscore = currscore + coder - teamlo; 
                    if(nextcurrscore > x) continue;
                    dp[nextcurrscore][coder] += add;
                    if(dp[nextcurrscore][coder] >= MOD) {
                        dp[nextcurrscore][coder] -= MOD;
                    }
                }
                //create a new team have to move the current state
                {
                    int nextcurrscore = currscore;
                    int nextlo = coder;
                    dp[nextcurrscore][nextlo] += add;
                    if(dp[nextcurrscore][nextlo] >= MOD) {
                        dp[nextcurrscore][nextlo] -= MOD;
                    }
                }
            }
        }
    }

    ll ans = 0;
    for(int i = 0; i <= x; i++) {
        for(int j = 0; j <= 100; j++) {
            ans += dp[i][j];
        }
    }

    cout << ans % MOD << '\n';

    return 0;
}