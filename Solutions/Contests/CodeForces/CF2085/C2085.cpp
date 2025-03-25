#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll x, y; cin >> x >> y;
    ll k = 0;
    int needdiff = 0;
    for(ll bit = 0; bit < 40; bit++) {
        // if(((x + k) >> bit) & ((y + k) >> bit) & 1LL) {
            // cout << "x : " << x << " y : " << y << " bit : " << bit << " xk : " << (((x + k) >> bit) & 1) << " yk : " << (((y + k) >> bit) & 1) << '\n';
            // k += 1LL << bit;
        // }
        // if(((x >> bit) & 1) & ((y >> bit) & 1)) {
            // needdiff = 1;
        // }
        // if(needdiff) k += 1LL << bit;
        // if(((x >> bit) & 1) ^ ((y >> bit) & 1)) {
            // needdiff = 0;
        // }
        
        if((((x + k) >> bit) & 1) ^ (((y + k) >> bit) & 1) && (((x + k) >> (bit + 1)) & 1) ^ (((y + k) >> (bit + 1)) & 1) == 0 || (((x + k) >> bit) & 1) & (((y + k) >> bit) & 1)) {
            k += 1LL << bit;
        }
    }
    if(x == y) cout << "-1\n";
    else {
        cout << k << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}
/*
100100100100100100100
010010010010010010100
*/