#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll b, c, d; cin >> b >> c >> d;

    for(int bit = 0; bit < 61; bit++) {
        int bb = ((b >> bit) & 1);
        int bc = ((c >> bit) & 1);
        if(bb && !bc) {
            d -= (1LL << bit);
        }
    }

    ll res = 0;
    for(int bit = 60; bit >= 0; bit--) {
        int bb = ((b >> bit) & 1);
        int bc = ((c >> bit) & 1);

        if(bb == bc && d >= (1LL << bit)) {
            d -= 1LL << bit;
            res ^= 1LL << bit;
        }
        if(bb && bc) {
            res ^= 1LL << bit;
        }
    }

    if(d == 0) {
        cout << res << '\n';
    } else {
        cout << "-1\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}