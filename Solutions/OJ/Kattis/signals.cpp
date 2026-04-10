#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> dp(n + 1, inf);

    dp[0] = 0;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        int pos = upper_bound(dp.begin(), dp.end(), x) - dp.begin();
        dp[pos] = x;
        res = max(res, pos);
    }

    cout << res << '\n';

    return 0;
}
