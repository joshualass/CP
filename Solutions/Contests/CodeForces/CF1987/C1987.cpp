#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll res = 0;
    for(int i = n - 1; i >= 0; i--) {
        res = max(a[i], res + 1);
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