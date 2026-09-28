#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m; cin >> n >> m;
    // ll n = 1'000'000'000'000'000LL, m = 300;
    vector<int> c(301);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        // int a = i + 1, b = i;
        c[a] = max(c[a], b);
    }

    int len = min(n + 1, 90001LL);
    // cout << "len : " << len << '\n';
    vector<int> dp(len);

    for(int i = 1; i < len; i++) {
        dp[i] = i;
        for(int j = 1; j <= min(i, 300); j++) {
            dp[i] = max(dp[i], dp[i - (j - c[j])] + j);
        }
    }

    ll res = 0;
    for(int i = 1; i < len; i++) {
        for(int j = 1; j <= min(i, 300); j++) {
            res = max(res, dp[i] + j * ((n - i) / (j - c[j])));
        }
    }

    cout << res << '\n';

    return 0;
}
