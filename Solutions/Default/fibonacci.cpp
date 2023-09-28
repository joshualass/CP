#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<int> dp(101);
    dp[1] = 1;
    for(int i = 2; i <= 100; i++) {
        dp[i] = (dp[i-1] + dp[i-2]) % MOD;
    }   
    int n; cin >> n;
    cout << dp[n-1] << "\n";
    return 0;
}