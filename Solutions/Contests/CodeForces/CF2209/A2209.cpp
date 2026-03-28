#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

void solve() {
    
    ll n, c, k; cin >> n >> c >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    for(int i = 0; i < n; i++) {
        if(a[i] <= c) {
            ll add = min(c - a[i], k);
            a[i] += add;
            k -= add;
            c += a[i];
        }
    }

    cout << c << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}