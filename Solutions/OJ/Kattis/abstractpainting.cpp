#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll power(ll base, ll power, ll mod = MOD) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%mod;
        }
        base = base*base%mod;
        power >>= 1;
    }
    return ans;
}

void solve() {
    int r, c; cin >> r >> c;
    cout << power(3,c+r) * power(2,r*c) % MOD << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}