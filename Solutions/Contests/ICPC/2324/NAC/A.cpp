#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> dp(n * 100000 + 1,1e9), next(n * 100000 + 1);

    dp[0] = 0;

    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        fill(next.begin(), next.end(), 1e9);

        for(int j = n * 100000; j >= 0; j--) {
            next[j] = dp[j] + b;
            if(j - a >= 0) {
                next[j] = min(next[j], dp[j - a]);
            }
        }
        int lo = 1e9;
        for(int j = 0; j <= n * 100000; j++) {
            lo = min(lo, next[j]);
            next[j] = lo;
        }

        swap(dp,next);

    }

    int res = 1e9;
    for(int i = 0; i <= n * 100000; i++) {
        res = min(res, max(i, dp[i]));
    }
    cout << res << '\n';
    return 0;
}