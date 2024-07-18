#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    vector<ll> a(k);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());
    ll res = 0;
    for(int i = 0; i < k - 1; i++) {
        res += a[i] * 2 - 1;
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