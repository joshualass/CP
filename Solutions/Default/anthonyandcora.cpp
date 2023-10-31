// https://open.kattis.com/problems/anthony

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
// template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
    for(auto &x : adj) {
        for(auto &y : x) os << y << " ";
        os << "\n";
    }
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    

    int n, m; cin >> n >> m;
    vector<vector<ld>> dp(n + 1,vector<ld>(m + 1));

    dp[n][m] = 1;
    
    for(int i = n + m - 1; i > 0; i--) {
        ld prob; cin >> prob;
        int currpoints = i + 1;
        for(int j = 1; j < currpoints; j++) {
            int apoints = j;
            int cpoints = currpoints - j;
            if(apoints <= n && cpoints <= m) {
                // ld starting_prob = dp[apoints][cpoints];
                // ld alose = starting_prob * prob;
                // ld awin = starting_prob - alose;
                // dp[apoints-1][cpoints] += awin;
                // dp[apoints][cpoints-1] += alose;
                ld starting_prob = dp[apoints][cpoints];

                ld awin = starting_prob * prob;
                ld alose = starting_prob - awin;

                dp[apoints][cpoints-1] += awin; //anthony wins, c loses a point
                dp[apoints-1][cpoints] += alose; //anthony loses, a loses a point

            }
        }
    }

    ld ans = 0;

    for(int i = 0; i <= n; i++) {
        ans += dp[i][0];
    }

    cout << fixed << setprecision(10) << ans << '\n';

    // cout << "dp: " << dp << '\n';

    return 0;
}