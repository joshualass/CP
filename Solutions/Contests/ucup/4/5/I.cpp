#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

ld dp[2001][5001][4];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<array<ll,6>> ar(n);
    for(auto &x : ar) for(auto &y : x) cin >> y;

    for(int i = n - 1; i >= 0; i--) {
        auto [A, B, C, D, E, P] = ar[i];
        ld a = A, b = B, c = C, d = D, e = E, p = P;
        for(int j = 0; j <= 5000; j++) {
            for(int k = 0; k < 4; k++) {
                ld best = 0;
                int f = 0;
                //do not go out to eat
                {
                    int nxi = i + 1;
                    int nxj = j - b;
                    int ok = 1;
                    ld util = 0;

                    if(nxj < 0) {
                        ok = 0;
                    } else {
                        //A pays
                        {
                            int nxk = k | 1;
                            if(p && dp[nxi][nxj][nxk] == -1) {
                                ok = 0;
                            } else {
                                util += p / 100 * (a + dp[nxi][nxj][nxk]);
                            }
                        }
                        //B pays
                        {
                            int nxk = k | 2;
                            if((100 - p) && dp[nxi][nxj][nxk] == -1) {
                                ok = 0;
                            } else {
                                util += (100 - p) / 100 * (a + dp[nxi][nxj][nxk]);
                            }
                        }

                    }
                    
                    if(ok) {
                        f = 1;
                        best = max(best, util);
                    }
                }

                //case go out to eat
                {
                    int nxi = i + 1;
                    int ok = 1;
                    ld util = 0;
                    if(k == 3) {
                        int nxj = j - e - d;
                        if(nxj < 0) {
                            ok = 0;
                        } else {
                            int nxk = 0;
                            if(dp[nxi][nxj][nxk] == -1) {
                                ok = 0;
                            } else {
                                util = c + dp[nxi][nxj][nxk];
                            }
                        }
                    } else {
                        int nxj = j - d;
                        if(nxj < 0) {
                            ok = 0;
                        } else {
                            //A pays
                            {
                                int nxk = k | 1;
                                if(p && dp[nxi][nxj][nxk] == -1) {
                                    ok = 0;
                                } else {
                                    util += p / 100 * (c + dp[nxi][nxj][nxk]);
                                }
                            }
                            //B pays
                            {
                                int nxk = k | 2;
                                if((100 - p) && dp[nxi][nxj][nxk] == -1) {
                                    ok = 0;
                                } else {
                                    util += (100 - p) / 100 * (c + dp[nxi][nxj][nxk]);
                                }
                            }
                        }
                    }

                    if(ok) {
                        f = 1;
                        best = max(best, util);
                    }
                }

                if(f) {
                    dp[i][j][k] = best;
                } else {
                    dp[i][j][k] = -1;
                }
            }
        }
    }

    cout << fixed << setprecision(12) << dp[0][m][0] << '\n';

    return 0;
}
