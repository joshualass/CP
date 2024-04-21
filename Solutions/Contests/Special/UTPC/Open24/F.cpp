#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    vector<vector<ll>> mat(n,vector<ll>(m));
    for(auto &x : mat) for(auto &y : x) cin >> y;

    vector<vector<ll>> rpref(n,vector<ll>(m));
    vector<vector<ll>> cpref(m,vector<ll>(n));

    for(ll i = 0; i < n; i++) {
        for(ll j = 1; j < m; j++) {
            rpref[i][j] = rpref[i][j-1] + mat[i][j-1];
        }
    }

    for(ll i = 0; i < m; i++) {
        for(ll j = 1; j < n; j++) {
            cpref[i][j] = cpref[i][j-1] + mat[j-1][i];
        }
    }

    vector<vector<ll>> dp(n,vector<ll>(m,LLONG_MAX));
    dp.back().back() = 0;
    for(int i = n - 1; i >= 0; i--) {
        for(int j = m - 1; j >= 0; j--) {
            if(i != n - 1) {
                dp[i][j] = dp[i+1][j] + (cpref[j][i] * cpref[j][i]);
            }
            if(j != m - 1) {
                dp[i][j] = min(dp[i][j], dp[i][j+1] + (rpref[i][j] * rpref[i][j]));
            }
        }
    }
    cout << dp[0][0] << '\n';
    return 0;
}