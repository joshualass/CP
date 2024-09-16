#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n, m; cin >> n >> m;

    vector<vector<int>> dp(n + 1, vector<int>(5,-MOD));
    dp[0][0] = 0;

    vector<char> cycle = {'n', 'a', 'r', 'e', 'k'};
    set<char> chat = {'n', 'a', 'r', 'e', 'k'};

    for(int i = 0; i < n; i++) {
        string s; cin >> s;
        for(int startptr = 0; startptr < 5; startptr++) {
            int cur = startptr;
            int bad = 0;
            for(int j = 0; j < m; j++) {
                if(s[j] == cycle[cur % 5]) {
                    cur++;
                } else if(chat.count(s[j])) {
                    bad++;
                }
            }

            int delta = ((cur - startptr) - bad);
            // cout << "i : " << i << " sp : " << startptr << " delta : " << delta << "c : " << cur << " bad : " << bad << '\n';
            dp[i+1][cur % 5] = max(dp[i+1][cur % 5], dp[i][startptr] + delta);
            dp[i+1][startptr] = max(dp[i+1][startptr],dp[i][startptr]);

        }

    }

    // for(int i = 0; i < 5; i++) {
    //     cout << dp[n][i] << '\n';
    // }

    int res = 0;
    for(int i = 0; i < 5; i++) {
        res = max(res, dp[n][i] - i * 2);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}