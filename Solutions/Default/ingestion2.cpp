#include <bits/stdc++.h>
typedef long double ld;
using namespace std;

const int SIZE = 103;

int apps[SIZE];
int dp[SIZE][SIZE][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    apps[0] = m;
    for(int i = 1; i < SIZE; i++) {
        apps[i] = apps[i-1] * 2 / 3;
    }

    int foods[n];
    for(int &x : foods) cin >> x;

    for(int c = 1; c < SIZE; c++) {
        for(int r = 0; r < SIZE - 1; r++) {
            if(r != 0) {
                // dp[r][c][0] = max(dp[r-1][c-1][0] + min(foods[c-1],apps[r-1]), dp[r][c][0]);
                dp[r][c][1] = max(dp[r-1][c-1][0],dp[r-1][c-1][1]) + min(foods[c-1],apps[r-1]); //best eating scenario
                dp[r][c][0] = max(dp[r+1][c-1][1],dp[r+1][c-1][0]); //best no eat scenario
            } else {
                dp[r][c][0] = max(dp[r+1][c-1][1],dp[r+1][c-1][0]); //best no eat scenario                
            }
            dp[0][c][0] = max(dp[r][c-1][0], dp[0][c][0]);
        }
    }

    int most = 0;
    for(int r = 0; r < SIZE; r++) {
        most = max(most,dp[r][n][0]);
        most = max(most,dp[r][n][1]);
    }
    cout << most << '\n';
    return 0;
}