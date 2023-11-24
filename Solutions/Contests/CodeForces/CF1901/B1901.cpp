#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    ll ans = 0;
    vector<ll> v(n);
    
    for(auto &x: v) cin >> x;

    v.push_back(0);
    ll prev = 0;
    for(int i = 0; i < v.size(); i++) {
        if(v[i] >= prev) {
            prev = v[i];
        } else {
            ans += prev - v[i];
        }
        prev = v[i];
    }
    cout << ans - 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}