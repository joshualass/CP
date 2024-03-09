#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int SIZE = 105;
ld lds[SIZE] = {};
int mults[SIZE] = {};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    lds[0] = m;
    // mults[1]=m;
    for (int i = 1; i < SIZE; i++) {
        lds[i] = lds[i - 1] * 2 / 3;
        mults[i] = (int)(lds[i - 1] + 0.000000000001);
        // mults[i] = mults[i-1]*2/3;
    }
    for (int i = 0; i < SIZE; i++) {
        // cout << mults[i] << '\n';
    }
    int dp[SIZE][SIZE] = {};
    
    for (int c = 0; c < n; c++) {
        int cals; cin >> cals;
        for (int r = 0; r < SIZE - 1; r++) {
            dp[r+1][c+1] = max(dp[r+1][c+1], dp[r][c] + min(cals, mults[r]));
            if(r != 0) {
                dp[r-1][c+1] = max(dp[r-1][c+1], dp[r][c]);
            } else {
                // dp[r][c+1] = max(dp[r][c+1], dp[r][c]);
            }
        }
    }
    int most = 0;
    for (int i = 0; i < SIZE; i++) {
        most = max(dp[i][n], most);
    }

    for (int r = 0; r < 7; r++) {
        for (int c = 0; c < 6; c++) {
            cout << dp[r][c] << ' ';
        }
        cout << '\n';
    }
    cout << most;
    return 0;
}