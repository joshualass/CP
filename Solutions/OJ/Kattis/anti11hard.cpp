#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1'000'000'007;
//need to optimize with kmp
void solve() {
    int n; cin >> n;
    string b; cin >> b;
    // string b = "11";

    if(b.size() == 1) {
        cout << "1\n";
        return;
    }

    ll allergic = 0;
    for(int i = 0; i < b.size(); i++) {
        allergic <<= 1;
        allergic += b[i] - '0';
    }

    vector<vector<ll>> dp(n, vector<ll>(1 << b.size()));
    dp[0][0] = 1;
    dp[0][1] = 1;
    //always use pull-dp
    for(int i = 1; i < n; i++) {
        for(int bm = 0; bm < 1 << b.size(); bm++) {
            if(bm != allergic) {
                int prev1 = (bm >> 1);
                int prev2 = (bm >> 1) + (1 << (b.size() - 1));
                dp[i][bm] += dp[i-1][prev1];
                dp[i][bm] += dp[i-1][prev2];
                dp[i][bm] %= MOD;
            }
        }
    }
    ll res = 0;
    for(int i = 0; i < 1 << b.size(); i++) {
        res += dp[n-1][i];
    }
    cout << res % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}