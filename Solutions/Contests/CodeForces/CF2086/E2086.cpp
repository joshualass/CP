#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
uniquely determine a string by having all coeffs <= 3 with the only coeff = 4 being the last 
*/

ll cnt_zebra(ll x, ll k) {
    if(x == 0) return 0;

    vector<ll> a;
    ll t = 6148914691236517205LL;

    for(int i = 0; i < 32; i++) {
        if(a.size() || x / t) {
            a.push_back(x / t);
        }
        x -= x / t * t;
        t /= 4;
    }

    vector dp(a.size() + 1, vector(k + 1, vector(5, vector<ll>(2))));
    // cout << "x : " << x << " a : " << a << '\n';

    dp[0][0][0][1] = 1;
    for(int i = 0; i < a.size(); i++) {
        for(int j = 0; j <= k; j++) {
            for(int l = 0; l <= 4; l++) {
                for(int m = 0; m < 2; m++) {
                    if(m == 0) {

                        for(int n = 0; n <= (l == 4 ? 0 : 4); n++) {
                            if(j + n <= k) {
                                dp[i+1][j + n][max(l, n)][0] += dp[i][j][l][m];
                            }
                        }

                    } else {

                        for(int n = 0; n <= (l == 4 ? 0 : a[i]); n++) {
                            if(j + n <= k) {
                                dp[i+1][j + n][max(l, n)][n == a[i]] += dp[i][j][l][m];
                            }
                        }

                    }
                }
            }
        }
    }

    ll res = 0;
    for(int i = 0; i <= 4; i++) for(int j = 0; j < 2; j++) res += dp[a.size()][k][i][j];
    return res;

}

void solve() {
    ll l, r, k; cin >> l >> r >> k;
    if(k >= 100) {
        cout << "0\n";
        return;
    }
    cout << cnt_zebra(r, k) - cnt_zebra(l - 1, k) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}