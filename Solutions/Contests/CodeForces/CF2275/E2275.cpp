#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
when stuck stuck, spend some time to reread the prpoblem ...........
ig sick nerf D:
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> a(2, vector<int>(n));

    for(auto &x : a) 
        for(auto &y : x) 
            cin >> y;

    vector<int> suf(n);
    for(int i = n - 2; i >= 0; i--) {
        for(int t = 1; t < 2; t++) {
            suf[i] = max(suf[i], (a[0][i] == a[t][i + 1]) + (a[1][i] == a[t ^ 1][i + 1]));
        }
        if(i == n - 2) {
            suf[i] += a[0][n - 1] == a[1][n - 1];
        }
        suf[i] += suf[i + 1];
    }

    // cout << "suf : " << suf << endl;

    int res = 0;
    vector dp(n, vector<int>(4, -1e9));

    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 4; j++) {
            if(j < 2) {
                if(i) {
                    for(int t = 0; t < 2; t++) {
                        if(t != j) {
                            dp[i][j] = max(dp[i][j], dp[i-1][2 + t] + (a[t][i-1] == a[j][i]));
                        }
                    }
                }
            } else {
                //take from neighbor
                dp[i][j] = max(dp[i][j], dp[i][j ^ 3] + (a[0][i] == a[1][i]));
                //try crosses
                // if(i){
                //     for(int t = 0; t < 2; t++) {
                //         int here = j & 1;
                //         int cost = (a[t][i-1] == a[here ^ 1][i]) + (a[here ^ 1][i] == a[t ^ 1][i-1]) + (a[t ^ 1][i-1] == a[here][i]);
                //         dp[i][j] = max(dp[i][j], dp[i-1][t] + cost);
                //     }
                // }
            }
            if(i == n - 1) {
                if(j >= 2) {
                    // cout << "i : " << i << " j : " << j << " val : " << dp[i][j] + suf[i] << endl;
                    res = max(res, dp[i][j] + suf[i]);
                }
            } else {
                if(j < 2) {
                    // cout << "i : " << i << " j : " << j << " dp : " << dp[i][j] << " val : " << dp[i][j] + suf[i] << endl;
                    res = max(res, dp[i][j] + suf[i]);
                }
            }
        }
    }

    cout << res + n * 2 - 1 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}