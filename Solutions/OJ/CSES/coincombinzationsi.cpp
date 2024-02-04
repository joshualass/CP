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
    for(auto &y:coins) cin >> y;
    vector<ll> dp(x+1);
    dp[0] = 1;
    for(ll i = 0; i <= x; i++) {
        dp[i] %= MOD;
        for(auto coin : coins) {
            if(coin + i <= x) {
                dp[coin+i] += dp[i];
                while(dp[coin+1] > MOD) {
                    dp[coin+1] -= MOD;
                }
            }
        }
    }   
    cout << dp[x] << "\n";
    return 0;
}