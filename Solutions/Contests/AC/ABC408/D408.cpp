#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int inf = 1e9;

void solve() {
    
    int n; cin >> n;
    string s; cin >> s;

    vector<array<int,3>> dp(n + 1, array<int,3>{inf, inf, inf});

    dp[0][0] = 0;
    for(int i = 0; i < n; i++) {
        dp[i+1][0] = dp[i][0] + (s[i] == '1');
        dp[i+1][1] = min(dp[i][0], dp[i][1]) + (s[i] == '0');
        dp[i+1][2] = min(dp[i][1], dp[i][2]) + (s[i] == '1');
    }

    cout << *min_element(dp[n].begin(), dp[n].end()) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}