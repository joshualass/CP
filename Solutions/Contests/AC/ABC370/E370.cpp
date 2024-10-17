#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    // vector<ll> dp(n + 1);

    // dp[0] = 1;

    // ll totalsum = 1;

    // ll sum = 0;
    // ll lo = 0;

    // for(int i = 1; i <= n; i++) {
    //     sum += a[i-1];
    //     while(sum > k) {
    //         sum -= a[lo++];
    //     }
    //     dp[i] = totalsum;
    //     if(sum == k) {
    //         dp[i] = (dp[i] + MOD - dp[lo]) % MOD;
    //     }
    //     totalsum = (totalsum + dp[i]) % MOD;
    // }

    // cout << dp[n] << '\n';

    //sum of everything in the map
    ll totalways = 1;
    //number of ways for the current last element to form a subsequence. 
    ll finalways = -1;
    map<ll,ll> dp;
    dp[0] = 1;

    ll cursum = 0;

    for(int i = 0; i < n; i++) {
        cursum += a[i];
        ll addways = (totalways + MOD - dp[cursum - k]) % MOD;
        dp[cursum] = (dp[cursum] + addways) % MOD;
        totalways = (totalways + addways) % MOD;
        finalways = addways;
    }

    cout << finalways << '\n';

    return 0;
}