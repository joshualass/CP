#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;
const ll INF = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k; cin >> n >> k;
    vector<ll> p(k);
    for(ll &x : p) cin >> x;
    ll res = 0;
    for(int i = 1; i < 1 << k; i++) {
        ll c = 1;
        bool ok = 1;
        for(int j = 0; j < k; j++) {
            if((i >> j) & 1) {
                if(INF / p[j] < c) {
                    ok = 0;
                    break;
                }
                c *= p[j];
            }
        }
        if(ok) {
            if(__builtin_popcount(i) & 1) {
                res += n / c;
            } else {
                res -= n / c;
            }
        }
    }

    cout << res << '\n';

    return 0;
}