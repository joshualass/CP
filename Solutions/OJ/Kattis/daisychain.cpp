#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int d, t, w, n; cin >> d >> t >> w >> n;
    int threeneed = t, twoneed = d - t;

    int mx3 = d; //we never consider any state with more than this many available 3 prongs
    int mx2 = twoneed;

    vector<array<int,3>> p(n);
    for(auto &x : p) {
        for(auto &y : x) {
            cin >> y;
        }
    }

    sort(p.begin(), p.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[2] > rhs[2];
    });

    vector<vector<ll>> dp(mx3 + 1, vector<ll>(mx2 + 1, inf)), ndp;
    dp[min(mx3, w)][0] = 0;

    for(auto [p, two, three] : p) {
        ndp.assign(mx3 + 1, vector<ll>(mx2 + 1, inf));
        three--;
        for(int i = 0; i <= mx3; i++) {
            for(int j = 0; j <= mx2; j++) {
                //take
                if(i + three >= 0) {
                    int nxi = min(mx3, i + three);
                    int nxj = min(mx2, j + two);
                    ndp[nxi][nxj] = min(ndp[nxi][nxj], dp[i][j] + p);
                }
                ndp[i][j] = min(ndp[i][j], dp[i][j]);
            }
        }
        swap(dp, ndp);
    }

    ll res = inf;
    for(int i = 0; i <= mx3; i++) {
        for(int j = 0; j <= mx2; j++) {
            // cout << "i : " << i << " j : " << j << " dp[i][j] : " << dp[i][j] << endl;
            if(i >= threeneed + twoneed - j) {
                res = min(res, dp[i][j]);
            }
        }
    }

    if(res == inf) res = -1;
    cout << res << '\n';

    return 0;
}
