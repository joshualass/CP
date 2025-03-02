#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//towers placed - 1, last type placed (row, col), coord cnts

ll dp[4][2][2000][2000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll r, c; cin >> r >> c;
    vector<string> a(r);
    for(auto &x : a) cin >> x;

    // ll r = 2000, c = 2000;
    // vector<string> a(2000);
    // for(int i = 0; i < 2000; i++) {
    //     a[i] = string(2000, '.');
    // }

    vector<ll> er(r), ec(c);
    for(ll i = 0; i < r; i++) {
        for(ll j = 0; j < c; j++) {
            if(a[i][j] == '.') {
                er[i]++;
                ec[j]++;
            }
        }
    }

    auto get_cnt_r = [&](ll r, ll cnt) -> ll {
        ll res = 1;
        for(ll i = 2; i <= cnt; i++) {
            res *= er[r] - i;
        }
        return res;
    };

    auto get_cnt_c = [&](ll c, ll cnt) -> ll {
        ll res = 1;
        for(ll i = 2; i <= cnt; i++) {
            res *= ec[c] - i;
        }
        return res;
    };

    for(ll i = 0; i < 2; i++) {
        for(ll j = 0; j < r; j++) {
            for(ll k = 0; k < c; k++) {
                dp[0][i][j][k] = a[j][k] == '.';
            }
        }
    }

    for(ll i = 0; i < 3; i++) {
        for(ll j = 0; j < 2; j++) {
            for(ll k = 1; i + k < 4; k++) {
                if(j == 0) {
                    vector<ll> add_per_col(c);
                    for(ll l = 0; l < r; l++) {
                        for(ll m = 0; m < c; m++) {
                            ll add = dp[i][j][l][m] * get_cnt_c(m, k);
                            add_per_col[m] += add;
                            dp[i + k][j ^ 1][l][m] -= add;
                        }
                    }
                    for(ll l = 0; l < r; l++) {
                        for(ll m = 0; m < c; m++) {
                            if(a[l][m] == '.') {
                                dp[i + k][j ^ 1][l][m] += add_per_col[m];
                            }
                        }
                    }   
                } else {
                    vector<ll> add_per_row(r);
                    for(ll l = 0; l < r; l++) {
                        for(ll m = 0; m < c; m++) {
                            ll add = dp[i][j][l][m] * get_cnt_r(l, k);
                            add_per_row[l] += add;
                            dp[i + k][j ^ 1][l][m] -= add;
                        }
                    }
                    for(ll l = 0; l < r; l++) {
                        for(ll m = 0; m < c; m++) {
                            if(a[l][m] == '.') {
                                dp[i + k][j ^ 1][l][m] += add_per_row[l];
                            }
                        }
                    }
                }
            }
        }
    }

    ll res = 0;
    for(ll i = 0; i < 2; i++) {
        for(ll j = 0; j < r; j++) {
            for(ll k = 0; k < c; k++) {
                res += dp[3][i][j][k];
            }
        }
    }

    // for(ll i = 0; i < 4; i++) {
    //     for(ll j = 0; j < 2; j++) {
    //         cout << "i : " << i << " j : " << j << '\n';
    //         for(ll k = 0; k < r; k++) {
    //             for(ll l = 0; l < c; l++) {
    //                 cout << dp[i][j][k][l] << " ";
    //             }
    //             cout << '\n';
    //         }
    //         cout << '\n';
    //     }
    // }

    cout << res << '\n';

    return 0;
}