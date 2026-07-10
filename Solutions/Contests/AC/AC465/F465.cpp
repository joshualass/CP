#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int maxn = 1000000;

ll dp[maxn], cnts[maxn];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> p10 = {1, 10, 100, 1000, 10000, 100000, 1000000};
    int n; cin >> n;

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        ll x; cin >> x;
        cnts[stoi(s)] += x;
    }

    for(int i = 0; i < maxn; i++) {
        int num = i;
        dp[num] += cnts[num];
        for(int bm = 1; bm < 1 << 6; bm++) {
            int nx = num, ok = 1;
            for(int j = 0; j < 6; j++) {
                int d = num / p10[5 - j] % 10;
                if((bm >> j) & 1) {
                    if(d) {
                        nx -= p10[5 - j];
                    } else {
                        ok = 0;
                    }
                }
            }
            if(ok) {
                // if(ok && i == 3) {
                //     cout << "bm : " << bm << " nx : " << nx << endl;
                // }
                if(__builtin_popcount(bm) % 2) {
                    dp[num] += dp[nx];
                } else {
                    dp[num] -= dp[nx];
                }
            }
        }
    }

    // for(int i = 0; i < maxn; i++) {
    //     cout << "i : " << i << " dp[i] : " << dp[i] << '\n';
    // }

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        string l, r; cin >> l >> r;
        int ok = 1;
        for(int i = 0; i < 6 ; i++) {
            if(l[i] > r[i]) ok = 0;
        }
        ll res = 0;
        // cout << "qq : " << qq << endl;
        if(ok) {
            // cout << "ok, res = dp[stoi(r)] : " << dp[stoi(r)] << endl;
            for(int bm = 0; bm < 1 << 6; bm++) {
                int num = 0;
                int ok = 1;
                for(int j = 0; j < 6; j++) {
                    if((bm >> j) & 1) {
                        if(l[j] - '0') {
                            num += (l[j] - '0' - 1) * p10[5 - j];
                        } else {
                            ok = 0;
                        }
                    } else {
                        num += (r[j] - '0') * p10[5 - j];
                    }
                }
                if(ok) {
                    // cout << "bm ok : " << bm << " num : " << num << endl;
                    if(__builtin_popcount(bm) % 2) {
                        // cout << "sub : " << dp[num] << endl;
                        res -= dp[num];
                    } else {
                        // cout << "add : " << dp[num] << endl;
                        res += dp[num];
                    }
                }
            }
        }
        cout << res << '\n';
    }

    return 0;
}
