#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int recur(int i) {
    if(i <= 1) {
        return 1;
    } else {
        return recur(i - 1) + recur(i - 2);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    // cout << "Number of ways travel calculated by Recursion: " << recur(n) << "\n";

    vector<ll> dp;
    dp.resize(n+1);

    dp[0] = 1;
    dp[1] = 1;
    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i - 2];
    }

    cout << "Number of ways to travel calculated by Dynamic Programming: " << dp[n] << "\n";

    return 0;
}