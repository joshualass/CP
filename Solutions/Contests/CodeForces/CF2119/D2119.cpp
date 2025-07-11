#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
intution is not very strong, but we see that n = 5000, so we should assume some n^2 dp
there is one obvious state which is dp on how many future elements we need to take. 
the important observation to make is that for a future op, it will be limited by some element which we place later. 
and if we remove some element at index i, it doesn't matter which higher index j it came from because the number of options is the same.

also, missed the transitions where previous op takes and we say that this op will add to later ops. 

p important ...

barrett does the mod calculations fast. 
*/

void solve() {
    
    ll n, m; cin >> n >> m;

    vector<ll> dp(n + 1), ndp(n + 1);

    dp[0] = 1;

    for(int i = n; i > 0; i--) {
        ndp.assign(n + 1, 0);

        for(int j = 0; j <= n; j++) {
            if(j) ndp[j-1] = (ndp[j-1] + dp[j] * i * j) % m;
            ndp[j] = (ndp[j] + dp[j] * (1 + i + i * j)) % m;
            if(j + 1 <= n) ndp[j+1] = (ndp[j+1] + dp[j]) % m;
            // AC
            // //case some op takes here
            // //case a[i] is positive and takes here
            // ndp[j] = (ndp[j] + dp[j] * i) % m;
            // //case taken by previous op
            // //put a 0 here
            // if(j) ndp[j-1] = (ndp[j-1] + dp[j] * i * j) % m;
            // //put a positive number here
            // ndp[j] = (ndp[j] + dp[j] * i * j) % m;

            // //case no op is taking here
            // //no op
            // ndp[j] = (ndp[j] + dp[j]) % m;
            // //some op
            // if(j + 1 <= n) ndp[j+1] = (ndp[j+1] + dp[j]) % m;

            // ndp[j] = (dp[j] * (i + 1)) % m;
            // if(j + 1 <= n) {
            //     ndp[j] = (ndp[j] + dp[j+1] * i) % m;
            // }
            // if(j) ndp[j] = (ndp[j] + dp[j-1] * j) % m;

            // ndp[j] = (ndp[j] + dp[j]) % m;
            // if(j) ndp[j-1] = (ndp[j-1] + dp[j] * i * j) % m;
            // ndp[j] = (ndp[j] + dp[j] * i) % m;
            // if(j + 1 <= n) ndp[j+1] = (ndp[j+1] + dp[j]) % m;


            // take later
            // if(j + 1 <= n) ndp[j+1] = (ndp[j+1] + dp[j]) % m;
            // //take here/this element not taken at all
            // ndp[j] = (ndp[j] + dp[j] * (i + 1)) % m;
            // //taken from prev op
            // if(j) ndp[j-1] = (ndp[j-1] + dp[j] * i) % m;
            // if(j) {
            //     ndp[j] = (ndp[j] + dp[j] * i * j) % m;
            // }
        }

        swap(dp, ndp);
    }

    // for(int i = 1; i <= n; i++) {
    //     ndp.assign(n + 1, 0);
    //     for(int j = 0; j <= n; j++) {

    //     }
    //     swap(dp, ndp);
    // }

    cout << dp[0] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}