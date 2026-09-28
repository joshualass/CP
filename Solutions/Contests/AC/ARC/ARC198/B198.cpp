#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll x, y, z; cin >> x >> y >> z;
    // cout << (y <= x * 2 && z < x ? "Yes" : "No") << '\n';

    // cout << (y <= x * 2 && z < x && (y % 2 == 0 || z) ? "Yes" : "No") << '\n';

    cout << (y <= x * 2 && z <= x && (y % 2 == 0 || z) ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}