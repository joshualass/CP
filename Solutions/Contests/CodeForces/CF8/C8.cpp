#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll dp[1 << 24];
int p[1 << 24];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int xs, ys; cin >> xs >> ys;

    auto get_dist = [&](array<int,2> a, array<int,2> b) -> ll {
        return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]);
    };

    int n; cin >> n;
    vector<array<int,2>> a(n);
    for(auto &x : a) {
        cin >> x[0] >> x[1];
        x[0] -= xs;
        x[1] -= ys;
    }

    for(int i = 0; i < 1 << n; i++) dp[i] = 1e18;

    dp[0] = 0;

    for(int bm = 1; bm < 1 << n; bm++) {
        int i = __builtin_ctz(bm);

        p[bm] = bm - (1 << i);
        dp[bm] = dp[bm - (1 << i)] + get_dist({0, 0}, a[i]) * 2;

        for(int j = i + 1; j < n; j++) {
            if((bm >> j) & 1) {
                int par = bm - (1 << i) - (1 << j);
                ll cost = dp[par] + get_dist({0,0}, a[i]) + get_dist(a[i], a[j]) + get_dist(a[j], {0,0});
                if(cost < dp[bm]) {
                    dp[bm] = cost;
                    p[bm] = par;
                }
            }
        }

        // cout << "bm : " << bm << " dp[bm] : " << dp[bm] << '\n';
    }

    cout << dp[(1 << n) - 1] << '\n';

    int cur = (1 << n) - 1;
    cout << "0";

    while(cur) {
        int nx = p[cur];
        // cout << "cur : " << cur << " nx : " << nx << '\n';
        for(int i = 0; i < n; i++) {
            if(((cur ^ nx) >> i) & 1) {
                cout << " " << i + 1;
            }
        }
        cout << " 0";
        cur = nx;
    }

    cout << '\n';

    return 0;
}
