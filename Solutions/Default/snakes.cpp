// http://www.usaco.org/index.php?page=viewproblem2&cpid=945
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[400][401];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("snakes.in","r",stdin);
    // freopen("snakes.out","w",stdout);
    int n, K; cin >> n >> K;
    vector<int> snakes(n);
    for(auto &x: snakes) cin >> x;
    // sort(snakes.begin(),snakes.end());
    int least = INT_MAX;
    for(int i = 0; i < n; i++) { //encounter each snakes
        fill(begin(dp[i]),begin(dp[i])+401,-1);
        for(int j = 0; j <= i; j++) { //for each encounter, try starting at every swap count possible
            int curr_size = 0;
            int wasted = 0;
            for(int k = i; k >= j; k--) {//for each swap count, find the best starting point
                if(snakes[k] > curr_size) {
                    wasted += (snakes[k] - curr_size) * (i - k);
                    curr_size = snakes[k];
                } else {
                    wasted += curr_size - snakes[k];
                }
                if(k == 0) { //start at beginning
                    if(j == 0) { //still on original net
                        if(dp[i][j] == -1) {
                            dp[i][j] = wasted;
                        } else {
                            dp[i][j] = min(dp[i][j], wasted);
                        }
                    } //if taking from beginning, not necessary to consider swapping a net
                } else {
                    if(j != 0 && dp[k-1][j-1] != -1) { //if still on original net, not possible ... 
                        if(dp[i][j] == -1) {
                            dp[i][j] = dp[k-1][j-1] + wasted;
                        } else {
                            // cout << "assigning: " << dp[k-1][j-1] << " k: " << k << " j: " << j;
                            dp[i][j] = min(dp[i][j], dp[k-1][j-1] + wasted);
                        }
                    }
                }
            }
                // cout << "i: " << i << " J: " << j << " " << dp[i][j] << "\n";
            if(i == n - 1 && j <= K) {
                least = min(least, dp[i][j]);
            }
        }
    }
    cout << least << "\n";

    return 0;
}