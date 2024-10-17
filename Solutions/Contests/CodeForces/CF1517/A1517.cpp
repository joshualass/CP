#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll num; cin >> num;
    ll res = 0;
    while(num >= 2050) {
        ll sub = 2050;
        while(sub * 10 <= num) sub *= 10;
        res++;
        num -= sub;
    }
    if(num) {
        cout << "-1\n";
    } else {
        cout << res << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}