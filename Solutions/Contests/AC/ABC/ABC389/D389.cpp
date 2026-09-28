#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll r; cin >> r;
    ll res = 1;

    ll p = r - 1;
    for(ll i = 0; i < r; i++) {
        while(p && sqrt((((ld) i) + 0.5) * (((ld) i) + 0.5) + (((ld) p) + 0.5) * (((ld) p) + 0.5)) > r) p--;
        res += p * 4;
    }

    cout << res << '\n';

    return 0;
}