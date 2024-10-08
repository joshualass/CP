#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll hisqrt(ll k) {
    ll start = sqrt(k);
    while(start * start > k) {
        start--;
    }
    while((start + 1) * (start + 1) <= k) {
        start++;
    }
    return start;
}

void solve() {
    ll k; cin >> k;

    ll add = 0;
    while(add != hisqrt(k + add)) {
        add = hisqrt(k + add);
    }
    cout << k + add << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}