#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

void solve() {
    int n; cin >> n;
    vector v(3, vector<int>(n));
    for(auto &vvv : v) {
        for(auto &vvvvv : vvv) cin >> vvvvv;
    }

    vector dp(n, vector<int>(8));

    for(int i = 0; i < n; i++) {
        for(int d = 1; d < 8; d++) {
            for(int e = 0; e < 3; e++) {
                if((d >> e) & 1) {
                    dp[i][d] = max(v[e][i],dp[i][d]);
                    if(i != 0) {
                        dp[i][d] = max(dp[i][d], dp[i-1][d ^ (1 << e)] + v[e][i]);
                    }
                }
            }
            if(i != 0) {
                dp[i][d] = max(dp[i][d],dp[i-1][d]);
            }
        }
    }

    // cout << "v\n" << v << "dp\n" << dp << '\n';

    cout << (dp[n-1][7]) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}