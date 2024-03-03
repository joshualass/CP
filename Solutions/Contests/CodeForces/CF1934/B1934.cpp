#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;
vector<int> dp(1000,INT_MAX);

void solve() {
    int n; cin >> n;
    int ans = max(0,(n-960)/15);
    n -= ans * 15;
    ans += dp[n];
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> tris = {1,3,6,10,15};
    dp[0] = 0;
    for(int i = 1; i < 1000; i++) {
        for(int j = 0; j < 5; j++) {
            if(i-tris[j] >= 0) {
                dp[i] = min(dp[i],dp[i-tris[j]]+1);
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}