#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int INF = 1e9;

//x_i, fuel_to, fuel_from, gassed up
int dp[301][301][301][2];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i <= 300; i++) for(int j = 0; j <= 300; j++) for(int k = 0; k <= 300; k++) for(int l = 0; l < 2; l++) dp[i][j][k][l] = INF;

    int n, h; cin >> n >> h;
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) cin >> a[i];
    vector<int> p(n+1), f(n+1);
    for(int i = 1; i < n; i++) cin >> p[i] >> f[i];

    for(int i = 0; i <= h; i++) {
        dp[0][h][i][0] = 0;
    }

    for(int i = 0; i < n; i++) {
        for(int l = 0; l < 2; l++) {
            for(int j = 0; j <= h; j++) {
                for(int k = 0; k <= h; k++) {
                    if(dp[i][j][k][l] < INF) {
                        // cout << "i : " << i << " j : " << j << " k : " << k << " l : " << l << " dp[i][j][k][l] : " << dp[i][j][k][l] << '\n';
                        if(l) { //fueled up ready to go
                            int d = a[i+1] - a[i];
                            if(j >= d && k + d <= h) {
                                dp[i+1][j-d][k+d][0] = min(dp[i+1][j-d][k+d][0], dp[i][j][k][l]);
                            }
                        } else { //consider fueling
                            dp[i][j][k][1] = min(dp[i][j][k][1], dp[i][j][k][0]); //no gas
                            dp[i][min(j+f[i], h)][k][1] = min(dp[i][min(j+f[i], h)][k][1], dp[i][j][k][0] + p[i]);
                            dp[i][j][max(k - f[i],0)][1] = min(dp[i][j][max(k - f[i],0)][1], dp[i][j][k][0] + p[i]);
                        }
                    }
                }
            }
        }
    }

    int res = INF;
    for(int to = 0; to <= h; to++) {
        for(int from = 0; from <= to; from++) {
            res = min(res, dp[n][to][from][0]);
        }
    }

    cout << (res >= INF ? -1 : res) << '\n';

    return 0;
}