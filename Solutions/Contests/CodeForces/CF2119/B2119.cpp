#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;

    ll px, py, qx, qy; cin >> px >> py >> qx >> qy;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    sort(a.begin(), a.end());
    ld len = sqrtl((px - qx) * (px - qx) + (py - qy) * (py - qy));

    cout << (accumulate(a.begin(), a.end(), 0LL) >= len && len >= a.back() - accumulate(a.begin(), a.end() - 1, 0LL) ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}