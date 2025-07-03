#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    ll best_min = 1e18;
    ll next_min = 1e18;
    ll res = LLONG_MAX;

    for(ll i = 1; i < n; i++) {
        ll d = a[i] - a[i-1];
        res = min(res, d + best_min);
        best_min = min(best_min, next_min);
        next_min = d;
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