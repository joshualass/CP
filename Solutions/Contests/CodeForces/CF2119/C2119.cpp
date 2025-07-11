#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, l, r, k; cin >> n >> l >> r >> k;
    ll hi = 1LL << (64 - __builtin_clzll(l));

    if(n == 2) {
        cout << "-1\n";
    } else if(n & 1) {
        cout << l << '\n';
    } else {
        if(hi <= r) {
            if(k >= n - 1) {
                cout << hi << '\n';
            } else {
                cout << l << '\n';
            }
        } else {
            cout << "-1\n";
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}