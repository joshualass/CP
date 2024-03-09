#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll a, b, r; cin >> a >> b >> r;
    ll diff = 0;
    for(int bit = 60; bit >= 0; bit--) {
        if(diff > 0) {
            if((a & (1LL << bit)) && ((b & (1LL << bit)) == 0) && r >= (1LL << bit)) {
                diff -= (1LL << bit) * 2;
                r -= 1LL << bit;
            }
        }
        if(diff < 0) {
            if((b & (1LL << bit)) && ((a & (1LL << bit)) == 0) && r >= (1LL << bit)) {
                diff += (1LL << bit) * 2;
                r -= 1LL << bit;
            }           
        }
        diff += a & (1LL << bit);
        diff -= b & (1LL << bit);
    }
    cout << abs(diff) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}