#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    if((n - 1) % 4 <= 1) {
        cout << "0\n";
        return 0;
    }
    ll target = n * (n + 1) / 4;
    vector<ll> dp(target+1);
    dp[0] = 1;
    for(ll num = 1; num <= n; num++) {
        for(ll i = target; i >= 1; i--) {
            if(i - num >= 0) {
                dp[i] += dp[i-num];
                while(dp[i] >= MOD) {
                    dp[i] -= MOD;
                }
            }
        }
    }
    if(dp[target] % 2) {
        dp[target] += MOD;
    }
    cout << (dp[target] / 2)%MOD << "\n";

    return 0;
}