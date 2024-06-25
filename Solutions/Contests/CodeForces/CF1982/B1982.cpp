#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll x, y, k; cin >> x >> y >> k;
    
    for(int i = 0; i < 50; i++) {
        ll add1 = min(k, y - (x - x / y * y));
        k -= add1;
        x += add1;
        while(x % y == 0) x /= y;
    }
    // cout << "x : " << x << " y : " << y << " k : " << k << '\n';
    if(k == 0) {
        cout << x << '\n';
    } else {
        assert(x == 1);
        cout << x + (k % (y-1)) << '\n';;
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}