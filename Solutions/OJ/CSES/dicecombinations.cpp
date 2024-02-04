#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const int N = 1e6 + 1;
const ll MOD = 1e9 + 7;
ll dp[N];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    for(int i = 1; i <= 6; i++) {
        dp[i] = 1;
    }
    for(int i = 2; i < N; i++) {
        for(int j = 1; j <= min(6,i - 1); j++) {
            dp[i] += dp[i-j];
        }
        dp[i] %= MOD;
    }
    cout << dp[n] << "\n";
    return 0;
}