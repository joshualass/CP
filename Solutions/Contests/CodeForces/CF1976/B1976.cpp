#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n; cin >> n;
    vector<ll> a(n), b(n+1);
    for(ll &x : a) cin >> x;
    for(ll &x : b) cin >> x;

    ll mindiff = INT_MAX;
    ll res = 0;
    for(int i = 0; i < n; i++) {
        res += abs(a[i] - b[i]);
        mindiff = min(mindiff,abs(a[i]-b[n]));
        mindiff = min(mindiff,abs(b[i]-b[n]));
        if(b[n] >= min(a[i],b[i]) && b[n] <= max(a[i],b[i])) mindiff = 0;
    }
    cout << res + mindiff + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}