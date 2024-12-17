#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> a(n), b(n);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    vector<ll> c(n);
    ll res = 0;
    for(ll i = 0; i < n; i++) {
        if((i & 1)) {
            c[i] = a[i] - b[i];
            res += b[i];
        } else {
            c[i] = b[i] - a[i];
            res += a[i];
        }
    }

    sort(c.rbegin(),c.rend());

    for(ll i = 0; i < n / 2; i++) {
        res += c[i];
    }

    cout << res << '\n';

    return 0;
}