#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<int> ra(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        ra[x] = i;
    }
    vector<int> dp(n + 1, -1);
    int res = 0;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;

        int idx = ra[x - 1];

        int l = 0, r = n;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(dp[m] == -1 || dp[m] > idx) {
                r = m - 1;
            } else {
                l = m;
            }
        }

        dp[l + 1] = idx;
        res = max(res, l + 1);

    }

    cout << "2 " << res + 1 << '\n';

    return 0;
}
