#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[1 << 16][121];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 1 << 16; i++) for(int j = 0; j < 121; j++) dp[i][j] = -1;

    int n; cin >> n;
    vector<array<int,3>> a(n);
    for(int i = 0; i < n; i++) {
        char c; cin >> c;
        int r, b; cin >> r >> b;
        a[i] = {c == 'R', r, b};
    }    

    dp[0][0] = 0;
    for(int bm = 0; bm < 1 << n; bm++) {
        for(int i = 0; i < 121; i++) {
            if(dp[bm][i] != -1) {
                int rc = 0, bc = 0;
                for(int j = 0; j < n; j++) {
                    if((bm >> j) & 1) {
                        if(a[j][0] == 1) {
                            rc++;
                        } else {
                            bc++;
                        }
                    }
                }

                for(int j = 0; j < n; j++) {
                    if(((bm >> j) & 1) == 0) {
                        int sr = min(a[j][1], rc), sb = min(a[j][2], bc);
                        dp[bm + (1 << j)][i + sr] = max(dp[bm + (1 << j)][i + sr], dp[bm][i] + sb);
                    }
                }
            }
        }
    }

    //total red, total blue
    int tr = 0, tb = 0;
    for(int i = 0; i < n; i++) {
        tr += a[i][1], tb += a[i][2];
    }

    int res = INT_MAX;
    for(int i = 0; i < 121; i++) {
        if(dp[(1 << n) - 1][i] != -1) {
            int sr = i, sb = dp[(1 << n) - 1][i];
            res = min(res, max(tr-sr,tb-sb));
        }
    }

    cout << res + n << '\n';

    return 0;
}