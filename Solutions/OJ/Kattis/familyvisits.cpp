#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, d; cin >> n >> d;
    vector<array<int,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    vector<int> dp(n + 1);
    vector<int> ndp(n + 1);

    vector<int> z(n);
    for(int i = 0; i < d; i++) {
        int x; cin >> x;
        x--;
        z[x] = 1;
    }

    for(int i = 0; i < n; i++) {
        ndp.assign(n + 1, -1);
        for(int j = 0; j < n; j++) {
            if(dp[j] != -1) {
                dp[j] += a[i][0];
                //no clean
                if(ndp[j] == -1 || dp[j] < ndp[j]) {
                    ndp[j] = dp[j];
                }
                //clean
                ndp[j+1] = max(0, dp[j] - a[i][1]);
            }
        }

        if(z[i]) {
            for(int j = 0; j <= n; j++) {
                if(ndp[j] > 0) ndp[j] = -1;
            }
        }

        dp = ndp;
    }

    for(int i = 0; i <= n; i++) {
        if(dp[i] >= 0) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << "-1\n";

    return 0;
}
