#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll res = 0;
    if(k == 1) {
        for(int i = 0; i < n; i++) {
            if(i) {
                res = max(res, a[i] + a[0]);
            }
            if(i != n - 1) {
                res = max(res, a[i] + a[n-1]);
            }
        }
    } else {
        sort(a.begin(), a.end());
        for(int i = n - k - 1; i < n; i++) res += a[i];
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