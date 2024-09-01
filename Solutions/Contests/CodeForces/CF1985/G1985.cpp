#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1'000'000'007;

/*
make observation - k >= 10 -> impossible because a digit cannot increase value by 10.
*/

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

void solve() {

    ll l, r, k; cin >> l >> r >> k;
    if(k >= 10) {
        cout << "0\n";
        return;
    }

    ll maxdig = 9 / k;
    
    cout << (binexp(maxdig + 1, r) - binexp(maxdig + 1, l) + MOD) % MOD << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}