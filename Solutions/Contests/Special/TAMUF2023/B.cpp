#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld l, d, x; cin >> l >> d >> x;

    ll ans = 0;

    while(l / (l + d) < x / 100) {
        ans++;
        l++;
    }

    cout << ans << '\n';

    return 0;
}