#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

ll getops(array<ll,5> a) {
    sort(a.begin(), a.end());
    ll ops = a[3];
    ll left = max(0LL, a[0] + a[1] + a[2] - a[3]);
    ll res;
    if((a[4] - a[3]) * 2 <= left) {
        res = (2 + left + (a[4] - a[3])) / 3 + ops;
    } else {
        ll t = (left + 1) / 2;
        res = ops + t + (1 + a[4] - a[3] - t) / 2;
    }
    // cout << "a : " << a << " res : " << res << endl;
    return res;
}

ll dp[2][100][100][100];

map<array<ll,5>, ll> ttfang;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // auto solve_slow = [&](auto self, array<ll,5> z) -> ll {
    //     // cout << "ss z : " << z << endl;
    //     if(ttfang.count(z) == 0) {
    //         ll res = LLONG_MAX;
    //         if(z == array<ll,5>{0,0,0,0,0}) {
    //             res = 0;
    //         } else {
    //             for(int i = 0; i < 5; i++) {
    //                 auto t = z;
    //                 if(t[i]) {
    //                     t[i] = max(0LL, t[i] - 2);
    //                     res = min(res, 1 + self(self, t));
    //                 }
    //             }
    //             for(int i = 0; i < 5; i++) {
    //                 for(int j = i + 1; j < 5; j++) {
    //                     for(int k = j + 1; k < 5; k++) {
    //                         auto t = z;
    //                         if(t[i] || t[j] || t[k]) {
    //                             if(t[i]) t[i]--;
    //                             if(t[j]) t[j]--;
    //                             if(t[k]) t[k]--;
    //                             res = min(res, 1 + self(self, t));
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //         ttfang[z] = res;
    //     }
    //     return ttfang[z];
    // };

    // auto check_ops = [&](array<ll,5> z) -> void {
    //     if(solve_slow(solve_slow, z) != getops(z)) {
    //         cout << "slow : " << solve_slow(solve_slow, z) << " fast : " << getops(z) << endl;
    //         assert(0);
    //     }
    // };

    // int mx = 15;

    // for(int i = 0; i < mx; i++) {
    //     for(int j = i; j < mx; j++) {
    //         for(int k = j; k < mx; k++) {
    //             for(int l = k; l < mx; l++) {
    //                 for(int z = l; z < mx; z++) {
    //                     array<ll,5> zz = {i, j, k, l, z};
    //                     check_ops(zz);
    //                 }
    //             }
    //         }
    //     }
    // }

    int n; cin >> n;
    vector<int> c(n);
    vector<array<ll,5>> a(n);
    vector<array<int,5>> cp(n + 1);

    for(int i = 0; i < n; i++) {
        cin >> c[i];
        c[i]--;
        for(int j = 0; j < 5; j++) {
            cp[i+1][j] += cp[i][j];
        }
        cp[i+1][c[i]]++;
        for(auto &x : a[i]) cin >> x;
    }

    auto cleardp = [&](int idx) -> void {
        for(int i = 0; i < 100; i++) {
            for(int j = 0; j < 100; j++) {
                for(int k = 0; k < 100; k++) {
                    dp[idx][i][j][k] = LLONG_MAX;
                }
            }
        }
    };

    cleardp(0), cleardp(1);
    dp[1][0][1][2] = 0;

    for(int last = 3; last + 1 < n; last++) {
        // cout << "last : " << last << endl;
        int cur = last & 1;
        int nx = cur ^ 1;
        cleardp(nx);
        for(int i = 0; i < last; i++) {
            for(int j = i + 1; j < last; j++) {
                for(int k = j + 1; k < last; k++) {
                    int l = last;
                    assert(dp[cur][i][j][k] != LLONG_MAX);
                    array<int,5> cards = cp[last + 1];
                    cards[c[i]]--;
                    cards[c[j]]--;
                    cards[c[k]]--;
                    cards[c[l]]--;

                    // cout << "i : " << i << " j : " << j << " cards : " << cards << endl;

                    //take i
                    {
                        array<ll,5> cost = a[i];
                        for(int z = 0; z < 5; z++) cost[z] = max(0LL, cost[z] - cards[z]);
                        dp[nx][j][k][l] = min(dp[nx][j][k][l], dp[cur][i][j][k] + getops(cost));
                    }
                    //take j
                    {
                        array<ll,5> cost = a[j];
                        for(int z = 0; z < 5; z++) cost[z] = max(0LL, cost[z] - cards[z]);
                        dp[nx][i][k][l] = min(dp[nx][i][k][l], dp[cur][i][j][k] + getops(cost));
                    }
                    //take k
                    {
                        array<ll,5> cost = a[k];
                        for(int z = 0; z < 5; z++) cost[z] = max(0LL, cost[z] - cards[z]);
                        dp[nx][i][j][l] = min(dp[nx][i][j][l], dp[cur][i][j][k] + getops(cost));
                    }
                    //take l
                    {
                        array<ll,5> cost = a[l];
                        for(int z = 0; z < 5; z++) cost[z] = max(0LL, cost[z] - cards[z]);
                        dp[nx][i][j][k] = min(dp[nx][i][j][k], dp[cur][i][j][k] + getops(cost));
                    }
                }
            }
        }
    }

    ll res = LLONG_MAX;
    int last = n - 1;
    int cur = last & 1;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            for(int k = j + 1; k + 1 < n; k++) {
                // cout << "cur : " << cur << " i : " << i << " j : " << j << " k : " << k << " val : " << dp[cur][i][j][k] << endl;
                assert(dp[cur][i][j][k] != LLONG_MAX);
                res = min(res, dp[cur][i][j][k]);
            }
        }
    }

    // for(int i = 0; i < 10; i++) {
    //     for(int j = 0; j < 10; j++) {
    //         for(int k = 0; k < 10; k++) {
    //             if(dp[cur][i][j][k] != LLONG_MAX) cout << dp[cur][i][j][k] << endl;
    //         }
    //     }
    // }

    cout << res + n - 4 << '\n';

    return 0;
}
