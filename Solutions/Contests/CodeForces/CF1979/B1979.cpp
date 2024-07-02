#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int x, y; cin >> x >> y;
    int res = 1;
    for(int bit = 0; bit < 31; bit++) {
        if(((x >> bit) & 1) == ((y >> bit) & 1)) {
            res <<= 1;
        } else {
            break;
        }
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