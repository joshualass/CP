#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, l, r; cin >> n >> l >> r;

    ll ans = 0;

    for(ll bit = 0; bit < 63; bit++) {
        if((n >> bit) & 1) {
            ll num = 1LL << bit;
            ll next = (1LL << (bit + 1)) - 1;
            if(l > next || r < num) continue;
            ans += min(next, r) - max(num,l) + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}