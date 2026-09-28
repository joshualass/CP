#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    vector<vector<ll>> a(n);
    for(auto &x : a) {
        int l; cin >> l;
        x.resize(l);
        for(auto &y : x) cin >> y;
    }

    for(int i = 0; i < n; i++) {
        ll c; cin >> c;
        if(k <= sz(a[i]) * c) {
            cout << a[i][(k - 1) % sz(a[i])] << '\n';
            return 0;
        } else {
            k -= sz(a[i]) * c;
        }
    }

    return 0;
}
