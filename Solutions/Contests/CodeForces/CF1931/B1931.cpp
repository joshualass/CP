#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<ll> v(n);
    for(ll &x : v) cin >> x;
    ll per = reduce(v.begin(), v.end()) / n;
    ll leftover = 0;
    bool ok = 1;
    for(int i = 0; i < n; i++) {
        leftover += v[i] - per;
        if(leftover < 0) ok = 0;
    }
    cout << (ok ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}