// http://www.usaco.org/index.php?page=viewproblem2&cpid=863
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[10000];
/*
dp[i]
i - cows encountered
store - highest possible sum
*/

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    freopen("teamwork.in","r",stdin);
    freopen("teamwork.out","w",stdout);
    
    int n, k; cin >> n >> k;
    vector<int> v(n);
    for(auto &x: v)cin >> x;
    for(int i = 0; i < n; i++) {
        dp[i] = -1;
        int most = INT_MIN;
        for(int j = i; i - j < k && j >= 0; j--) {
            most = max(most, v[j]);
            // cerr << "moist: " << most << " ";
            if(dp[i] == -1) {
                if(j == 0) {
                    dp[i] = (i - j + 1) * most;
                } else {
                    dp[i] = (i - j + 1) * most + dp[j-1];
                }
            } else {
                if(j == 0) {
                    dp[i] = max(dp[i],(i - j + 1) * most);
                } else {
                    dp[i] = max((i - j + 1) * most + dp[j-1],dp[i]);
                }
            }
        }
        // cerr << "i: " << i << " dp[i]: " << dp[i] << " ";
    }
    // cerr << "\n";
    cout << dp[n-1];

    return 0;
}