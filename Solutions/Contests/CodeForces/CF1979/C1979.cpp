#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    ll g = 1;
    vector<ll> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        g = g * a[i] / gcd(g,a[i]);
    }

    ll cnt = 0;
    for(int i = 0; i < n; i++) {
        cnt += g / a[i];
    }
    if(cnt < g) {
        for(int i = 0; i < n; i++) {
            cout << g / a[i] << " \n"[i == n - 1];
        }
    } else {
        cout << "-1\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}