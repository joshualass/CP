#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, l, r; cin >> n >> l >> r;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    sort(v.begin(), v.end());
    ll ans = 0;
    ll lo = n, hi = n - 1;
    for(int i = 0; i < n; i++) {
        while(lo != 0 && v[i] + v[lo-1] >= l) lo--;
        while(hi != -1 && v[i] + v[hi] > r) hi--;
        ans += hi - lo + 1;
        if(i >= lo && i <= hi) ans--;
    }
    cout << ans / 2 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}