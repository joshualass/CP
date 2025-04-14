#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll lo = LLONG_MAX, idx = -1;
    for(ll i = 0; i < n; i++) {
        if(a[i] < lo) {
            lo = a[i];
            idx = i;
        }
    }
    a.erase(a.begin() + idx);
    ll g = 0;
    for(ll i = 0; i < a.size(); i++) {
        if(a[i] % lo == 0) g = gcd(g, a[i]);
    }
    cout << (lo == g ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}