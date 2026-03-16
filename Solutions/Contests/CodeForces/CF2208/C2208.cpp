#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;
    
    ld res = 0;
    for(int i = n - 1; i >= 0; i--) {
        res = max(res, res * (1 - ((ld) 1) / 100 * a[i][1]) + a[i][0]);
    }

    cout << fixed << setprecision(10) << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}