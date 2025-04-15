#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

/*
obs
add to zero - bad
uniform positive 

*/

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m, p; cin >> n >> m >> p;
    vector<vector<int>> dp(n + 1, vector<int>(n * m * 2 + 1));

    dp[0][n * m] = 1;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= n * m * 2; j++) {
            for(int k = -m; k <= m; k++) {

                if(j + k >= 0 && j + k <= n * m * 2) {
                    dp[i][j] += dp[i-1][j + k];
                    if(dp[i][j] >= p) dp[i][j] -= p;
                }

            }
        }
    }

    ll res = 1;
    for(int i = 0; i < n; i++) {
        res = res * (m * 2 + 1) % p;
    }
    res = (res - dp[n][n * m] + p) % p;
    res = (res + p - n * (m * 2)) % p;

    cout << res << '\n';

    return 0;
}