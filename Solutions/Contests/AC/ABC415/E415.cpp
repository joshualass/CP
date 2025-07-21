#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int h, w; cin >> h >> w;
    vector<vector<ll>> a(h, vector<ll>(w));

    for(auto &x : a) for(auto &y : x) cin >> y;
    vector<ll> p(h + w - 1);
    for(ll &x : p) cin >> x;

    ll l = 0, r = 1e18;
    vector dp(h, vector<ll>(w));
    while(l != r) {
        ll m = (l + r) / 2;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                dp[i][j] = -1;
            }
        }

        dp[0][0] = m;

        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(dp[i][j] != -1) {
                    dp[i][j] += a[i][j];
                    dp[i][j] -= p[(i + j)];
                    if(dp[i][j] >= 0) {
                        if(i + 1 < h) {
                            dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
                        }
                        if(j + 1 < w) {
                            dp[i][j+1] = max(dp[i][j+1], dp[i][j]);
                        }
                    }
                }
            }
        }

        if(dp[h-1][w-1] >= 0) {
            r = m;
        } else {
            l = m + 1;
        }

    }

    cout << l << '\n';

    return 0;
}
