#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll l = 1, r = 1e18;

    while(l != r) {
        ll m = (l + r) / 2;

        int matches = 0;
        for(int i = 1; i < n; i++) {
            if(a[i] - a[i-1] <= m) {
                i++;
                matches++;
            }
        }

        if(n - matches * 2 <= 1) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}