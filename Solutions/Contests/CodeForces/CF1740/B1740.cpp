#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n; cin >> n;
    ll res = 0, maxy = 0;

    for(ll i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        res += min(a,b);
        maxy = max(maxy, max(a,b));
    }
    cout << ((res + maxy) << 1)<< '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}