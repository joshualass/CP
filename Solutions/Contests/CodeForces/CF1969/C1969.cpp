#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<vector<ll>> dp(n+1,vector<ll>(k+1,1e18));

    for(int i = 0; i <= k; i++) {
        dp[0][i] = 0;
    }

    for(int i = 0; i < n; i++) {
        ll lo = 1e18;
        for(int op = 0; op <= k && i - op >= 0; op++) {
            lo = min(lo, a[i-op]);
            for(int prevop = 0; prevop + op <= k; prevop++) {
                dp[i+1][prevop + op] = min(dp[i-op][prevop] + lo * (op + 1),dp[i+1][prevop + op]);
            }
        }
    }
    // cout << dp << '\n';
    ll res = LLONG_MAX;
    for(int i = 0; i <= k; i++) {
        res = min(res, dp[n][i]);
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}