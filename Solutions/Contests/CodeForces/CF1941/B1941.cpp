#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    for(int i = 1; i < n - 1; i++) {
        ll cnt = v[i-1];
        v[i-1] -= cnt;
        v[i] -= cnt * 2;
        v[i+1] -= cnt;
        if(v[i-1] < 0 || v[i] < 0 || v[i+1] < 0) break;
    }
    cout << (count(v.begin(), v.end(),0) == n ? "Yes" : "No") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}