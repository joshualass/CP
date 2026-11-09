#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll res = 0;
    
    for(int k = 1; k <= n; k++) {
        if(n % k == 0) {
            ll lo = LLONG_MAX, hi = LLONG_MIN;
            for(int i = 0; i * k < n; i++) {
                ll s = 0;
                for(int j = 0; j < k; j++) {
                    s += a[i * k + j];
                }
                lo = min(lo, s);
                hi = max(hi, s);
            }
            res = max(res, hi - lo);
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}