#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll k, a, b, x, y; cin >> k >> a >> b >> x >> y;
    if(y < x) {
        swap(a, b);
        swap(x, y);
    }

    ll aops = k >= a ? 1 + (k - a) / x : 0;
    k -= aops * x;
    ll bops = k >= b ? 1 + (k - b) / y : 0;

    // cout << aops << ", " << bops << '\n';
    cout << aops + bops << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}