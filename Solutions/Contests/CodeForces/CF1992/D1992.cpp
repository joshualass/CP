#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    string s = "L";
    string a; cin >> a;
    s.append(a);
    s.push_back('L');

    vector<int> dp(s.size(), -1);
    dp[0] = k;

    for(int i = 0; i < dp.size(); i++) {
        if(dp[i] != -1) {
            if(s[i] == 'L') {
                for(int j = 1; j <= m && i + j < dp.size(); j++) {
                    dp[i + j] = max(dp[i], dp[i + j]);
                }
            } else if(s[i] == 'W') {
                dp[i+1] = max(dp[i] - 1, dp[i+1]);
            }
        }
    }

    cout << (dp.back() != -1 ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}