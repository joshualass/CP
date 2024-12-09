#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<vector<int>> a(2,vector<int>(n));
    for(auto &x : a) for(auto &y : x) cin >> y;

    int c = 0;

    for(int i = 0; i < n; i++) {
        c += max(a[0][i], a[1][i]);
    }

    int res = INT_MIN;
    for(int i = 0; i < n; i++) {
        res = max(res, c - max(a[0][i],a[1][i]) + a[0][i]+a[1][i]);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}