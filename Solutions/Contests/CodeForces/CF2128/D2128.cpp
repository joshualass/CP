#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll res = 0;

    for(int i = 0; i < n; i++) {
        //there are n - i paths that start at index i
        res += n - i;
        if(i) {
            if(a[i] < a[i-1]) {
                res += 1LL * (i - 1 + 1) * (n - i);
            }
        }
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}