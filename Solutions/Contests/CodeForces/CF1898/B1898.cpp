#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int n; cin >> n;
    ll ops = 0;
    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    ll lo = LLONG_MAX;

    for(int i = n - 1; i >= 0; i--) {
        if(v[i] <= lo) {
            lo = v[i];
        } else {
            ll curr_ops = (v[i] - 1) / lo;
            // cout << "i: " << i << " curr ops : " << curr_ops << " lo : " << lo <<  '\n';
            ops += curr_ops;
            lo = v[i] / (curr_ops + 1);
        }
    }
    cout << ops << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}