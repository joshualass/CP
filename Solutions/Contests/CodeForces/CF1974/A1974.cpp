#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int x, y; cin >> x >> y;
    cout << ((y + 1) / 2 + max(0,(x + 14 - (y + 1) / 2 * 15 + y * 4)/15)) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}