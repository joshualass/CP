#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    reverse(a.begin(), a.end());


    vector<vector<ll>> dp(10,vector<ll>(10)), ndp(10,vector<ll>(10));
    dp[0][0] = 1;
    for(int i = 0; i < n; i++) {
        ndp.assign(10,vector<ll>(10));
        for(int j = 0; j < min(10,a[i]); j++) {
            for(int k = 0; k < 10; k++) {
                for(int l = 0; l < 10; l++) {
                    if(i == 0 || j * 10 + k < a[i-1] && j * 10 + l < a[i-1]) {
                        ndp[j][k] += dp[k][l];
                    }
                }
            }
        }
        dp = ndp;
        ndp.assign(10,vector<ll>(10));
        for(int j = 0; j < 10; j++) {
            for(int k = 0; k < 10; k++) {
                for(int l = 0; l < 10; l++) {
                    if(j * 10 + k < a[i]) {
                        ndp[j][k] += dp[k][l];
                    }
                }
            }
        }
        dp = ndp;
    }

    ll res = 1;
    for(int &x : a) res *= x;
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            res -= dp[i][j];
        }
    }

    cout << res << '\n';

    return 0;
}