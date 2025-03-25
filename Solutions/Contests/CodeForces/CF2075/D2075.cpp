#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll dp[60][60][60];
ll dpbest[60][60];

void solve() {
    ll x, y; cin >> x >> y;
    ll res = 1e18;
    for(int i = 0; i < 60; i++) {
        for(int j = 0; j < 60; j++) {
            if((x>>i) == (y>>j)) res = min(res, dpbest[i][j]);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < 60; i++) for(int j = 0; j < 60; j++) {
        dpbest[i][j] = 1e18;
        for(int k = 0; k < 60; k++) dp[i][j][k] = 1e18;
    }

    dp[0][0][0] = 0;

    for(int i = 0; i < 60; i++) {
        for(int j = 0; j < 60; j++) {
            for(int k = 0; k < 60; k++) {
                for(int l = i + 1; l < 60; l++) {
                    //try adding to x
                    ll c = dp[i][j][k] + (1LL << l);
                    if(j + l < 60) {
                        dp[l][j+l][k] = min(dp[l][j+l][k], c);
                    }
                    //try adding ot y
                    c = dp[i][j][k] + (1LL << l);
                    if(k + l < 60) {
                        dp[l][j][k+l] = min(dp[l][j][k+l], c);
                    }
                    //try no adding ? 
                    dp[l][j][k] = min(dp[l][j][k], dp[i][j][k]);
                }   
                dpbest[j][k] = min(dpbest[j][k], dp[i][j][k]);
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    // cout << (1LL << 56) - 1;

    return 0;
}