#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    ll n, k, x; cin >> n >> k >> x;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll idx = n * k + 1;
    ll s = accumulate(a.begin(), a.end(), 0LL);
    while(x > s && idx > 0) {
        x -= s;
        idx -= n;
    }

    for(int i = n - 1; i >= 0; i--) {
        if(x > 0 && idx > 0) {
            x -= a[i];
            idx--;
        }
    }

    cout << (x <= 0 ? idx : 0) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}