#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k; cin >> n >> k;
    ll res = 0, mul = (n + 1), div = 2;
    while(n >= k) {
        if(n & 1) {
            res += mul / div;
        }
        mul *= 2;
        n /= 2;
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}