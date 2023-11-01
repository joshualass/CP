// https://codeforces.com/contest/1288/problem/C

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;

    vector<vector<ll>> dp(m, vector<ll>(n)); 

    //dp[i][j] stores the number of ways to have an array with length i and difference in elements j

    for(int i = 0; i < n; i++) {
        dp[0][i] = n - i;
    }

    for(int i = 0; i < m - 1; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k <= j; k++) {
                dp[i+1][k] += dp[i][j] * (j - k + 1);
                dp[i+1][k] %= MOD;
            }
        }
    }

    ll ans = 0;

    for(int i = 0; i < n; i++) {
        ans += dp[m-1][i];
    }

    cout << ans % MOD << '\n';

    // cout << "adj\n" << dp;

    return 0;
}