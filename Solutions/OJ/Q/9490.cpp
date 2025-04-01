#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));

    for(int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        a[l-1][r]++;
    }

    vector<vector<int>> p(n+1, vector<int>(n + 1));

    for(int len = 2; len <= n; len += 2) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            p[l][r] = p[l+2][r];
            for(int m = l + 2; m <= r; m += 2) {
                p[l][r] += a[l][m];
            }
        }
    }

    vector<vector<int>> dp(n+1,vector<int>(n+1));

    for(int len = 2; len <= n; len += 2) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            for(int m = l + 2; m < r; m += 2) {
                dp[l][r] = max(dp[l][r], dp[l][m] + dp[m][r]);
            }
            dp[l][r] = max(dp[l][r], dp[l+1][r-1]);
            dp[l][r] += a[l][r];
            dp[l][r] = max(dp[l][r], p[l][r]);
        }
    }

    for(int len = 1; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            for(int m = l + 1; m < r; m++) {
                dp[l][r] = max(dp[l][r], dp[l][m] + dp[m][r]);
            }
        }
    }

    cout << dp[0][n] << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m; cin >> n >> m;
//     vector<vector<int>> a(n+1,vector<int>(n+1));

//     for(int i = 0; i < m; i++) {
//         int l, r; cin >> l >> r;
//         a[l-1][r]++;
//     }    

//     vector<vector<int>> dp(n+1,vector<int>(n+1));

//     for(int len = 2; len <= n; len += 2) {
//         for(int l = 0; l + len <= n; l++) {
//             int r = l + len;

//             for(int m = l + 2; m < r; m += 2) {
//                 dp[l][r] = max(dp[l][r], dp[l][m] + dp[m][r]);
//             }

//             dp[l][r] = max(dp[l][r], dp[l+1][r-1]);
//             dp[l][r] += a[l][r];

//         }
//     }

//     for(int len = 1; len <= n; len++) {
//         for(int l = 0; l + len <= n; l++) {
//             int r = l + len;
//             for(int m = l + 1; m < r; m++) {
//                 dp[l][r] = max(dp[l][r], dp[l][m] + dp[m][r]);
//             }
//         }
//     }

//     for(auto x : dp) cout << x << '\n';

//     cout << dp[0][n] << '\n';

//     return 0;
// }
