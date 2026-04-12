#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k, p, q; cin >> n >> k >> p >> q;
    vector<ll> a(n), b(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x % p % q;
        b[i] = x % q % p;
    }

    
    vector<ll> pre(n + 1);
    for(int i = 0; i < n; i++) {
        pre[i+1] = pre[i] + min(a[i], b[i]);
    }
    a.insert(a.begin(), 0);
    b.insert(b.begin(), 0);
    for(int i = 1; i <= n; i++) {
        a[i] += a[i-1];
        b[i] += b[i-1];
    }

    ll res = LLONG_MAX;
    for(int l = 0; l + k <= n; l++) {
        res = min(res, pre[l] + min(a[l+k] - a[l], b[l+k] - b[l]) + (pre[n] - pre[l+k]));
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}