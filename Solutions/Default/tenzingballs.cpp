#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//just become better at doing dp

void solve() {
    int n; cin >> n;
    vector<int> dp(n+1);
    vector<int> best_before_val(n+1,1e9);
    for(int i = 1; i <= n; i++) {
        int num; cin >> num;
        dp[i] = min(dp[i-1] + 1, best_before_val[num]);
        best_before_val[num] = min(best_before_val[num],dp[i-1]);
    }
    cout << n - dp[n] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}