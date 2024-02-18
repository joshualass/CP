#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, x, y; cin >> n >> x >> y;
    ll ans = 0;
    map<pair<ll,ll>,ll> m;
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        if(m.count({num % x, num % y})) {
            ans += m[{num % x, num % y}];
        }
        m[{(x - num % x) % x, num % y}]++;
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