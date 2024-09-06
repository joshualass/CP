#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
dp state was tricky
lots of considerations, but I think I'm good enough to solve.

dp[i][j]
i - prefix i
j - prefix j charges used

Only special case to handle is when the charges overlap eachother. i.e. to charges i, j, i < j where i goes right and j goes left. 

Implementation tricky because dp is 1-indexed while a is 0-indexed.

*/

//ff paint charges too difficult
template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n; cin >> n;
    
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, MOD));

    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        dp[0][i] = 0; 
        for(int j = 1; j <= n; j++) {

            for(int k = 0; k < j; k++) {
                if(k + a[k] >= i) {
                    dp[i][j] = min(dp[i][j], dp[k][k] + 1);
                }
            }

            if(j >= i) {
                int back = max(0, i - a[i - 1]);
                dp[i][j] = min(dp[i][j], 1 + dp[back][i - 1]);
            }

            for(int k = 0; k < j; k++) {
                for(int l = k + 1; l < j; l++) {

                    if(a[k] > l - k + 1 && a[l] > l - k + 1 && k + a[k] >= i) {
                        int back = max(0, l + 1 - a[l]);
                        dp[i][j] = min(dp[i][j], 2 + dp[back][k]);
                    }

                }
            }

            for(int k = 0; k <= i; k++) {
                for(int l = j; l <= n; l++) {
                    dp[k][l] = min(dp[k][l], dp[i][j]);
                }
            }
        }
    }

    cout << dp[n][n] << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}