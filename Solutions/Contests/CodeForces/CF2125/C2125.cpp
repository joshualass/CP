#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll l, r; cin >> l >> r;


    auto cnt_leq = [&](ll a) -> ll {
        vector<int> p = {2, 3, 5, 7};
        ll res = 0;
        for(int i = 0; i < 1 << p.size(); i++) {
            ll m = 1;
            for(int j = 0; j < p.size(); j++) {
                if((i >> j) & 1) m *= p[j];
            }
            res += a / m * (__builtin_popcount(i) & 1 ? -1 : 1);
        }
        return res;
    };

    cout << cnt_leq(r) - cnt_leq(l - 1) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}