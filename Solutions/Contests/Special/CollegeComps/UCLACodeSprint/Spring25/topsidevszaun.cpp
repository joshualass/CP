#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
in andrew we trust. 
lower the constraints of the dp and try several random orders of the input.
*/

const int inf = 1e9;
int dp[301][300 * 300 + 1];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 301; i++) for(int j = 0; j < 300 * 300 + 1; j++) dp[i][j] = inf;
    
    dp[150][300 * 150] = 0;

    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        for(int j = 0; j <= 300 * 300; j++) {
            if(dp[i][j] >= 0) {
                //do not add anyone
                dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
                if(j + x <= 300 * 300) {
                    
                }
            }

        }
    }



    return 0;
}
