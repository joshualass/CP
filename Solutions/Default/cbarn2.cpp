//http://www.usaco.org/index.php?page=viewproblem2&cpid=622
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp [200][8][101];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, K; cin >> n >> K;
    vector<int> amts(n);
    for(auto &x : amts) cin >> x;
    for(int i = 0; i < 200; i++) {
        for(int j = 0; j < 101; j++) {
            for(int k = 0; k < 8; k++) { //start with always being able to reach 0 keys and not being able to start with any other keys
                if(k == 0) {
                    dp[i][k][j] = 0;
                } else {
                    dp[i][k][j] = -1;
                }
            }
        }
    }
    int least = INT_MAX;

    

    // for(int i = 0; i < n * 2; i++) { //rooms encountered
    //     for(int j = 1; j <= K; j++) { //keys opened
    //         for(int k = 1; k <= n; k++) { //rooms unlocked
    //             int curr = 0;
    //             for(int l = k-1; l >= 0 && i - l >= 0; l--) { //previous room 
    //                 cout << "i: " << i << " j: " << j << " k: " << k << " l: " << l << " value: " << dp[i-(k-l)+1][j-1][l] << " curr: " << curr << "\n";
    //                 curr += amts[(i-(k-l)+1)%n] * (k - l);
    //                 if(dp[i-(k-l)][j-1][l] != -1) {
    //                     if(dp[i][j][k] == -1) {
    //                         dp[i][j][k] = dp[i-(k-l)][j-1][l] + curr;
    //                     } else {
    //                         dp[i][j][k] = min(dp[i][j][k], dp[i-(k-l)][j-1][l] + curr);
    //                     }
    //                 }
    //             }
    //             if(dp[i][j][k] != -1 && k == n) {
    //                 cout << "i: " << i << " j: " << j << " k: " << k << " value: " << dp[i][j][k] << "\n";
    //                 least = min(least,dp[i][j][k]);
    //             }
    //         }
    //     }
    // }

    // for(int i = 0; i < n * 2; i++) {
    //     for(int k = 1; k <= K; k++) {
    //         for(int j = 1; j <= n; j++) {
    //             int curr = 0;
    //             for(int l = j; l > 0 && i >= l && i >= l; l--) {
    //                 curr += amts[l%n] * (j - l + 1);
    //                 if(dp[i][k][j] == -1) {
    //                     if(l == 0) {
    //                         dp[i][k][j] = dp[i]
    //                     } else {
    //                         dp[i][k][j] = curr + dp[i-l][k-1][l-1];
    //                     }
    //                 } else {
    //                     dp[i][k][j] = min(dp[i][k][j], curr + dp[i-l][k-1][l-1]);
    //                 }
    //             }
    //             if(k <= K && j == n) {
    //                 cout << "i: " << i << " j: " << j << " k: " << k << " value: " << dp[i][k][j] << "\n";
    //                 least = min(least, dp[i][k][j]);
    //             }
    //         }
    //     }
    // }
    cout << least << "\n";

    return 0;
}