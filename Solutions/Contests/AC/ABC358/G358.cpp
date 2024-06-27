#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int dx[5]{1, -1, 0, 0, 0}, dy[5]{0, 0, 1, -1, 0}; //UP, DOWN, RIGHT, LEFT


ll dp[2501][50][50];
ll mat[50][50];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 2501; i++) for(int j = 0; j < 50; j++) for(int k = 0; k < 50; k++) dp[i][j][k] = -1;
    
    int h, w, k; cin >> h >> w >> k;
    int si, sj; cin >> si >> sj;
    int stop = min(k,2500);

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cin >> mat[i][j];
        }
    }

    dp[0][si-1][sj-1] = 0;
    for(int i = 0; i < stop; i++) {
        for(int j = 0; j < h; j++) {
            for(int k = 0; k < w; k++) {
                if(dp[i][j][k] != -1) {
                    for(int l = 0; l < 5; l++) {
                        int newj = j + dx[l];
                        int newk = k + dy[l];
                        if(newj >= 0 && newj < h && newk >= 0 && newk < w) {
                            dp[i+1][newj][newk] = max(dp[i+1][newj][newk], dp[i][j][k] + mat[newj][newk]);
                        }
                    }
                }
            }
        }
    }

    ll res = 0;
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(dp[stop][i][j] != -1) {
                res = max(res, dp[stop][i][j] + (k - stop) * mat[i][j]);
            }
        }
    }

    cout << res << '\n';

    return 0;
}