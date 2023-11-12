// http://www.usaco.org/index.php?page=viewproblem2&cpid=494
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); 

    // freopen("guard.in","r",stdin);
    // freopen("guard.out","w",stdout);
    
    ll n, h; cin >> n >> h;
    vector<array<ll,3>> dp(1 << n);
    for(auto &x : dp) {
        x[2] = INT_MIN;
    }

    dp.front()[2] = INT_MAX;

    vector<array<ll,3>> cows(n);
    for(ll i = 0; i < n; i++) {
        cin >> cows[i][0];
        cin >> cows[i][1];
        cin >> cows[i][2];
    }

    vector<vector<ll>> bitcnts(n+1);
    for(ll i = 0; i < (1 << n); i++) {
        bitcnts[__builtin_popcount(i)].push_back(i);
        // cout << i << " " << __builtin_popcount(i) << '\n';
    }

    ll ans = INT_MIN;

    for(ll i = 0; i < n; i++) {
        for(auto x : bitcnts[i]) {
            for(ll j = 0; j < n; j++) {
                if(((x >> j) & 1) == 0) {
                    dp[x | (1 << j)] = {dp[x][0] + cows[j][0], dp[x][1] + cows[j][1], max(dp[x | (1 << j)][2], min(cows[j][2] - dp[x][1], dp[x][2]))};
                    if(dp[x | (1 << j)][0] >= h && dp[x | (1 << j)][2] >= 0) {
                        ans = max(ans, dp[x | (1 << j)][2]);
                    }
                }
            }
        }
    }
    // cout << ans << '\n';
    if(ans == INT_MIN) {
        cout << "Mark is too tall\n";
    } else {
        cout << ans << '\n';
    }

    return 0;
}