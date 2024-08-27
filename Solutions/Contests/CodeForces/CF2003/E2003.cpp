#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
notes
All the a elements must be less than all the b elements.

Observe: the a and b groups must be disjoint.
An element must be in one of 3 categories
1. In the 'a' group
2. in the 'b' group
3. not in either group

If an element is in any of the ranges, it must be in either category 1 or 2, else it must be in category 3. 
A given is that all these groups are disjoint. Most importantly, the a and b group.

Just need a good assignment now. 

Use dp. 
While doing the dp, we can assign the elements in category 3 to group a or b. 

dp[i][j][k] 

i - looking at prefix permutation i
j - using j indices belong to the 'a' group
k - last character is in 'a' or 'b' group

store -> {max inversions, reachable}

*/

//optimize memory
int dp[5001][5001][2][2];

void solve() {
    
    int n, m; cin >> n >> m;
    vector<int> starts(n), stops(n + 1);

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        starts[l-1]++;
        stops[r]++;
    }

    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            for(int k = 0; k < 2; k++) {
                for(int l = 0; l < 2; l++) {
                    dp[i][j][k][l] = 0;
                }
            }
        }
    }

    dp[0][0][0][1] = 1;
    dp[0][0][1][1] = 1;

    int res = -1;
    int active = 0;

    for(int i = 0; i < n; i++) {
        active -= stops[i];
        for(int j = 0; j <= i + 1; j++) {
            int cura = j;
            int curb = i - j + 1;
            if(stops[i+1] == 0 && cura) { //try to place an 'a' group here
                
                // cout << "consider placing a i : " << i << " j : " << j << '\n';

                if(dp[i][j-1][0][1]) {//we can always place an 'a' after an 'a'
                    // cout << "place a to a i : " << i << " j : " << j << '\n';
                    dp[i+1][j][0][0] = max(dp[i+1][j][0][0], dp[i][j - 1][0][0] + i);
                    dp[i+1][j][0][1] = 1;
                }

                if(active == 0 && dp[i][j-1][1][1]) {//no range overlap, so we can consider previously having a 'b'
                    // cout << "place b to a i : " << i << " j : " << j << '\n';
                    dp[i+1][j][0][0] = max(dp[i+1][j][0][0], dp[i][j - 1][1][0] + i);
                    dp[i+1][j][0][1] = 1;
                }

            }

            if(starts[i] == 0 && curb) { //try to place a 'b' group here

                // cout << "consider placing b i : " << i << " j : " << j << '\n';

                if(dp[i][j][0][1]) { //we can always place a 'b' after an 'a'
                    // cout << "place a to b i : " << i << " j : " << j << '\n';
                    dp[i+1][j][1][0] = max(dp[i+1][j][1][0], dp[i][j][0][0] + (curb - 1));
                    dp[i+1][j][1][1] |= dp[i][j][0][1];
                }

                if(dp[i][j][1][1]) { //we can always place a 'b' after a 'b'
                    // cout << "place b to b i : " << i << " j : " << j << '\n';
                    dp[i+1][j][1][0] = max(dp[i+1][j][1][0], dp[i][j][1][0] + (curb - 1));
                    dp[i+1][j][1][1] |= dp[i][j][1][1];
                } 

            }

            // if(dp[i+1][j][0][1]) {
            //     cout << "a poss here with i : " << i << " j : " << j << '\n';
            // }
            // if(dp[i+1][j][1][1]) {
            //     cout << "b poss here with i : " << i << " j : " << j << '\n';
            // }

            if(i + 1 == n) {

                if(dp[i+1][j][0][1]) {
                    res = max(res, dp[i+1][j][0][0]);
                }
                if(dp[i+1][j][1][1]) {
                    res = max(res, dp[i+1][j][1][0]);
                }

            }


        }

        active += starts[i];

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}