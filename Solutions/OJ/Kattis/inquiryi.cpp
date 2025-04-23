#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> p(n), s(n);
    for(ll i = 0; i < n; i++) {
        p[i] += a[i] * a[i];
        if(i) p[i] += p[i-1];
    }

    for(ll i = n - 1; i >= 0; i--) {
        s[i] += a[i];
        if(i != n - 1) s[i] += s[i+1];
    }

    ll res = 0;
    for(ll i = 0; i < n - 1; i++) {
        res = max(res, 1LL * p[i] * s[i+1]);
    }

    cout << res << '\n';

    return 0;
}
