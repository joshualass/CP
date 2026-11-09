#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

vector<int> dp[1 << 16];
int a[16];
int n;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];

    int res = INT_MAX;
    for(int i = 0; i < 1 << n; i++) dp[i].assign(1 << __builtin_popcount(i), -1);
    // for(int i = 0; i < 1 << n; i++) res = min(res, dfs((1 << n) - 1, i));

    for(int bm = 0; bm < 1 << n; bm++) {
        for(int left = 0; left < 1 << __builtin_popcount(bm); left++) {
            int min_prev = INT_MAX;
            if(bm == 0) {
                min_prev = 0;
            } else {
                int p = 0;
                int pre = 0, suf = left;
                for(int i = 0; i < n; i++) {
                    if((bm >> i) & 1) {
                        suf -= ((left >> p) & 1) << p;
                        if((left >> p) & 1) {
                            min_prev = min(min_prev, dp[bm ^ (1 << i)][pre + (suf >> 1)]);
                        } else {
                            min_prev = min(min_prev, dp[bm ^ (1 << i)][pre + (suf >> 1)]);
                        }
                        pre += ((left >> p) & 1) << p;
                        p++;
                    }
                }
            }
            int ls = 0, rs = 0, p = 0;
            for(int i = 0; i < n; i++) {
                if((bm >> i) & 1) {
                    if((left >> p) & 1) {
                        ls += a[i];
                    } else {
                        rs += a[i];
                    }
                    p++;
                }
            }
            min_prev = max(min_prev, abs(ls - rs));
            dp[bm][left] = min_prev;
            if(bm == (1 << n) - 1) res = min(res, dp[bm][left]);
        }
    }

    cout << res << '\n';

    return 0;
}