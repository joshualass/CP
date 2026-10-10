#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> dp(n + 1);
    for(int i = n - 1; i >= 0; i--) {
        dp[i] = max(dp[i + 1], a[i] + dp[min(n, i + m)]);
    }

    cout << dp[0] << '\n';

    return 0;
}
