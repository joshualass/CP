#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s1, s2; cin >> s1 >> s2;

    while(s1.size() && s2.size() && s1[0] == s2[0]) {
        s1 = s1.substr(1);
        s2 = s2.substr(1);
    }

    vector<vector<int>> dp(s1.size() + 1, vector<int>(s2.size() + 1));

    for(int i = 0; i < s1.size(); i++) {
        dp[i][0] = i;
    }

    for(int j = 0; j < s2.size(); j++) {
        dp[0][j] = j;
    }

    for(int i = 1; i <= s1.size(); i++) {
        for(int j = 1; j <= s2.size(); j++) {
            dp[i][j] = min(dp[i-1][j] + 1, dp[i][j-1] + 1);
            if(s1[i-1] == s2[j-1]) {
                dp[i][j] = min(dp[i][j], dp[i-1][j-1]);
            }
        }
    }

    // cout << "s1 sz : " << s1.size() << " s2 sz : " << s2.size() << " back : " << dp.back().back() << '\n';

    // cout << s1.size() - 1 + s2.size() - 1 + dp.back().back() << '\n';
    cout << s1.size() + s2.size() << '\n';

    return 0;
}