#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> dp(k);
    dp[0] = 1;

    int res = 1;

    for(int i = 1; i < n; i++) {
        int d = (a[i] - a[i-1] + k) % k;
        vector<int> ndp = dp;
        for(int j = 0; j < k; j++) {
            if(dp[j]) {
                ndp[(j + d) % k] = 1;
            }
        }
        dp = ndp;
        if(d) res++;
    }

    if(dp[a[0]]) res--;

    cout << res << '\n';

    return 0;
}
