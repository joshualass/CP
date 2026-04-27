#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

void solve() {
    
    int n; cin >> n;
    vector<string> a(2);
    for(auto &x : a) cin >> x;
    vector<int> dp(n + 1, inf);
    dp[0] = 0;

    for(int i = 1; i <= n; i++) {
        dp[i] = min(dp[i], dp[i-1] + (a[0][i-1] != a[1][i-1]));
        if(i >= 2) {
            dp[i] = min(dp[i], dp[i-2] + (a[0][i-2] != a[0][i-1]) + (a[1][i-2] != a[1][i-1]));
        }
    }

    cout << dp[n] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}