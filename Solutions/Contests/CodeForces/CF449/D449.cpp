#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
Andwerp recommended problem

Let's count the sequences that don't work with the help of inclusion/exclusion principles.

Problem: Count the number of elements for each x, 1 to n. s.t. a[i] & x = x;
Use SoS dp. 

I've solved SoS before, but clearly forgot how to do the technique :(

*/

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

const int MAXN = 20;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;

    vector<int> dp(1 << MAXN);
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        dp[a]++;
    }

    //do SoS, but in reverse
    for(int i = 0; i < MAXN; i++) {
        for(int bm = (1 << MAXN) - 1; bm >= 0; bm--) {
            if(((bm >> i) & 1) == 0) {
                dp[bm] += dp[bm + (1 << i)];
            }
        }
    }

    // for(int i = 0; i < 10; i++) {
    //     cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
    // }

    ll res = (binexp(2,n) + MOD - 1) % MOD;

    for(int bm = 1; bm < 1 << MAXN; bm++) {
        if(__builtin_popcount(bm) & 1) {
            res = (res - (binexp(2,dp[bm]) - 1) + MOD) % MOD;
        } else {
            res = (res + binexp(2,dp[bm]) + MOD - 1) % MOD;
        }
    }

    cout << res << '\n';

    return 0;
}