#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1'000'000'007;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> dp(n+1);
    dp[0] = 1;
    for(ll i = 1; i <= n; i++) {
        dp[i] = dp[i-1];
        if(i >= 2) {
            dp[i] += dp[i-2] * (i-1) * 2;
        }
        dp[i] %= MOD;
    }
    // cout << "dp : " << dp << '\n';
    int cnt = 0;
    for(int i = 0; i < k; i++) {
        int t1, t2; cin >> t1 >> t2;
        if(t1 == t2) {
            cnt++;
        } else {
            cnt += 2;
        }
    }
    cout << dp[n-cnt] << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}