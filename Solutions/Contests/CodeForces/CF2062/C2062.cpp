#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll res = accumulate(a.begin(), a.end(), 0LL);
    for(int i = 1; i < n; i++) {
        vector<ll> b(a.size() - 1);
        for(int j = 1; j < a.size(); j++) {
            b[j-1] = a[j] - a[j-1];
        }
        a = b;
        ll sum = accumulate(a.begin(), a.end(), 0LL);
        res = max({res, sum, -sum});
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