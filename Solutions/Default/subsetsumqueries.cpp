// https://atcoder.jp/contests/abc321/tasks/abc321_f
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int q, k; cin >> q >> k;
    vector<int> dp(k+1);
    dp[0] = 1;
    for(int i = 0; i < q; i++) {
        char type; cin >> type;
        int val; cin >> val;
        if(type == '+') {
            for(int j = k; j >= val; j--) {
                dp[j] = (dp[j] + dp[j-val]) % MOD;
                if(dp[j] >= MOD) dp[j] -= MOD;
            }
        } else if(type == '-') {
            for(int j = val; j <= k; j++) {
                dp[j] = (dp[j] - dp[j-val]) % MOD;
                if(dp[j] < 0) dp[j] += MOD;
            }
        }
        cout << dp[k] << '\n';
    }

    return 0;
}