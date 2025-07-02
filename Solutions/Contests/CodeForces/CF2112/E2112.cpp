#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int MAXN = 5e5;
const int inf = 1e9;
int dp[MAXN + 1]; //dp[i] stores the minimum number of nodes needed to make a tree with beauty i and having its root colored green

void solve() {
    
    int n; cin >> n;
    cout << (dp[n] >= inf ? -1 : dp[n]) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i <= MAXN; i++) dp[i] = inf;

    dp[1] = 1;
    for(int i = 1; i <= MAXN; i++) {
        if(i + 2 <= MAXN) {
            dp[i+2] = min(dp[i+2], dp[i] + 1);
        }
        for(int j = 1; i * j <= MAXN; j++) dp[i * j] = min(dp[i * j], dp[i] + dp[j] - 1);
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}