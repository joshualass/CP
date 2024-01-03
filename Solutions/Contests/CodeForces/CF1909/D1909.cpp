#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> v(n);

    for(auto &x : v) cin >> x;
    ll g = v[0] - k;
    for(int i = 1; i < n; i++) {
        g = gcd(g,v[i] - k);
    }
    cout << "g : " << g << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}