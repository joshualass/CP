#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, x; cin >> n >> x;
    vector<ll> coins(n);
    for(auto &y: coins) cin >> y;
    vector<ll> dp(x+1);
    dp[0] = 1;
    for(auto coin : coins) {
        for(ll i = 1; i <= x; i++) {
            if(i - coin >= 0) {
                dp[i] += dp[i-coin];
                
            }
            while(dp[i] >= MOD) {
                dp[i] -= MOD;
            }
        }
    }
    cout << dp[x] << "\n";
    return 0;
}