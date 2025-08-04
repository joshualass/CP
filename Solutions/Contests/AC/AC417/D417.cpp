#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int dp[10001][2001];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> p(n), a(n), b(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i] >> a[i] >> b[i];
    }

    for(int i = 0; i <= 2000; i++) dp[n][i] = i;
    for(int i = n - 1; i >= 0; i--) {
        for(int j = 0; j <= 2000; j++) {
            if(p[i] >= j) {
                dp[i][j] = dp[i+1][j + a[i]];
            } else {
                dp[i][j] = dp[i+1][max(0, j - b[i])];
            }
        }
    }

    vector<int> pf(n + 1);
    for(int i = 1; i <= n; i++) {
        pf[i] = pf[i-1] + b[i-1];
    }

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int x; cin >> x;
        int l = 0, r = n;
        while(l != r) {
            int m = (l + r) / 2;
            if(x - pf[m] <= 2000) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        x -= pf[l];
        
        cout << (l == n ? x : dp[l][x]) << '\n';
    }

    return 0;
}
