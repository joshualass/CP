#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ld> nums(n);

    for(auto &x : nums) cin >> x;

    vector dp(n + 1, vector<ld>(n+1));

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i-1][j-1] * 0.9 + nums[i-1]);
        }
    }
    ld ans = -100000000000000000;
    ld div = 0;
    for(int i = 1; i <= n; i++) {
        ld add = 1;
        for(int j = 1; j < i; j++) {
            add *= 0.9;
        }
        div += add;
        ans = max(ans, dp[n][i]/div - 1200/sqrt((ld)i));
    }
    cout << fixed << setprecision(10) << ans << '\n';
    return 0;
}