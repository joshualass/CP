#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto x : adj) {
        for(auto y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n, k; cin >> n >> k;
    //try pull dp
    vector<vector<ll>> dp(n+1,vector<ll>(k));
    for(ll i = 0; i <= n; i++) {
        for(ll j = 0; j < k; j++) {
            if(i == 0) {
                dp[i][j] = 1;
            } else {
                for(ll l = 0; i - (l + 1) * (j + 1) >= 0 && j + l < k; l++) {
                    // cout << "i : " << i - (l + 1) * (j + 1) << " j : " << l << '\n';
                    // cout << "i : " << i << " j : " << j << " l : " << l << " add from : " << i - (l + 1) * (j + 1) << " " << l << " add val : " << dp[i - (l + 1) * (j + 1)][l] << '\n';
                    dp[i][j] += dp[i - (l + 1) * (j + 1)][l];
                    if(dp[i][j] >= MOD) dp[i][j] %= MOD;
                }
            }
        }
    }
    // cout << "dp \n" << dp;
    ll ans = 0;
    for(int i = 0; i < k; i++) {
        ans += dp[n][i];
        if(ans >= MOD) ans %= MOD;
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}