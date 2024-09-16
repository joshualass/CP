#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << fixed << setprecision(15) << '\n';

    vector<ld> dp(100);

    dp[0] = 1;
    for(int i = 1; i < 100; i++) {
        dp[i] = .5 * dp[i-1] + (i >= 2 ? dp[i-2] * .5 : 0);
    }

    for(auto x : dp) {
        cout << x << '\n';
    }

    return 0;
}