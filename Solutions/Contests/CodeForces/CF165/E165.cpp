#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;


const int maxa = 22;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);

    for(int &x : a) cin >> x;

    vector<int> dp(1 << maxa, -1);
    for(int i = 0; i < n; i++) {
        dp[a[i]] = a[i];
    }

    for(int i = 0; i < maxa; i++) {
        for(int j = 0; j < 1 << maxa; j++) {
            if(j & (1 << i)) {
                dp[j] = max(dp[j], dp[j ^ (1 << i)]);
            }
        }
    }

    for(int i = 0; i < n; i++) {
        cout << dp[a[i] ^ ((1 << maxa) - 1)] << " \n"[i == n - 1];
    }

    return 0;
}