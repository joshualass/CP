#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int MAXN = 500;

bitset<MAXN> dpcc[MAXN][MAXN]; //dp_can_cover
int dp[MAXN][MAXN];
bool op[MAXN][MAXN]; //0/1 if op exists on this range

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        op[l][r] = 1;
    }

    for(int length = 1; length <= n; length++) {
        for(int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;
            //consider the union from the ops within the range[i,j-1]
            for(int k = i; k <= j - 1; k++) {
                if(dpcc[i][j-1][k]) {
                    dpcc[i][j][k] = 1;
                }
            }
            //consider the union from the ops within the range[i+1,j]
            for(int k = i + 1; k <= j; k++) {
                if(dpcc[i+1][j][k]) {
                    dpcc[i][j][k] = 1;
                }
            }
            //if op in range [i,j] exists, then all can be covered. 
            if(op[i][j]) {
                for(int k = i; k <= j; k++) {
                    dpcc[i][j][k] = 1;
                }
            }
        }
    }

    for(int length = 1; length <= n; length++) {
        for(int i = 0; i + length - 1 < n; i++) {
            int j = i + length - 1;
            //consider the transitions where we merge the 2 ranges disjoint ranges
            for(int k = i; k < j; k++) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j]);
            }
            //consider the transitions where we paint the extra element k black
            for(int k = i; k <= j; k++) {
                if(dpcc[i][j][k]) {
                    dp[i][j] = max(dp[i][j], dp[i][k-1] + 1 + dp[k+1][j]);
                }
            }
        }
    }

    cout << dp[0][n-1] << '\n';

    return 0;
}