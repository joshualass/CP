//https://codeforces.com/problemset/problem/1418/C
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 2e5+1;

int dp[N][2]; //stores friend's skips

void solve() {
    int n; cin >> n;
    for(int i = 0; i <= n; i++) {
        dp[i][0] = 1e9;
        dp[i][1] = 1e9;
    }
    dp[0][0] = 0;
    vector<int> v(n+1);
    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        for(int j = 0; j < 2; j++) {
            if(j) {
                dp[i][j] = dp[i-1][j^1] + v[i];
                if(i >= 2) {
                    dp[i][j] = min(dp[i][j], dp[i-2][j^1] + v[i] + v[i-1]);
                }
            } else {
                dp[i][j] = dp[i-1][j^1];
                if(i >= 2) {
                    dp[i][j] = min(dp[i][j],dp[i-2][j^1]);
                }
            }
        }
    }
    cout << min(dp[n][0], dp[n][1]) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}