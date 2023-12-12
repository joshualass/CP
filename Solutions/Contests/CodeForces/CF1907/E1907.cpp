#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll num; cin >> num;
    ll ans = 1;
    while(num != 0) {
        ll dig = num % 10;
        num /= 10;
        ans *= (dig + 1) * (dig + 2) / 2;
    }
    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}