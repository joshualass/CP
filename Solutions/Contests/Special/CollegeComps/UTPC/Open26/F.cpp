#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

//A, L are nice, but my time has come to do slpc

/*
range dp here.
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<vector<int>> a(n, vector<int>(n));
    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        l--; r--;
        a[l][r]++;
    }

    vector<vector<int>> b(n, vector<int>(n));
    for(int l = 0; l < n; l++) {
        int c = 0;
        for(int r = n - 1; r--; r >= l) {
            c += a[l][r];
            b[l][r] += c;
            if(l < r) a[l+1][r] += a[l][r];
        }
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(n + 1));

    for(auto x : b) cout << x << endl;

    for(int len = 1; len <= n; len++) {
        for(int l = 0; l + len <= n; l++) {
            int r = l + len;
            ll best = max(dp[l][r-1], dp[l+1][r]);
            dp[l][r] = best + b[l][r-1];
        }
    }

    cout << dp[0][n] << '\n';

    return 0;
}
