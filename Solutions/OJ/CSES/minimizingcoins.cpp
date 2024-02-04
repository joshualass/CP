#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x; cin >> n >> x;
    vector<int> v(n);
    for(auto &y: v) cin >> y;
    vector<int> dp(x+1,1e9);
    dp[0] = 0;
    for(auto coin : v) {
        for(int i = 1; i <= x; i++) {
            if(i - coin >= 0) {
                dp[i] = min(dp[i], dp[i-coin]+1);
            }
        }
    }
    cout << (dp[x] >= 1e9 ? -1 : dp[x]) << "\n";
    return 0;
}