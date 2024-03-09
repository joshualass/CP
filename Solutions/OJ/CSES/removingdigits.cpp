#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> dp(n+1,1e9);
    dp[n] = 0;
    for(int i = n; i > 0; i--) {
        if(dp[i] >= 1e9) continue;
        int copy = i;
        while(copy) {
            int digit = copy % 10;
            copy /= 10;
            dp[i-digit] = min(dp[i-digit],dp[i]+1);
        }
    }
    cout << dp[0] << "\n";
    return 0;
}