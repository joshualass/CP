#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, h, m; cin >> n >> h >> m;

    vector<int> dp(h + 1, m);
    vector<int> ndp(h + 1);

    int res = 0;

    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        ndp.assign(h + 1, -1);
        for(int j = 0; j <= h; j++) {
            if(dp[j] != -1) {
                if(j >= a) {
                    ndp[j - a] = max(ndp[j - a], dp[j]);
                }
                if(dp[j] >= b) {
                    ndp[j] = max(ndp[j], dp[j] - b);
                }
            }
        }

        dp = ndp;

        if(count(dp.begin(), dp.end(), -1) != h + 1) res++;

    }

    cout << res << '\n';

    return 0;
}
