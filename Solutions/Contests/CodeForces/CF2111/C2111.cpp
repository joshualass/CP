#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = LLONG_MAX;
    
    auto upd_cost = [&](int len, int ai) {
        res = min(res, 1LL * (n - len) * ai);
    };

    int p = 0, l = 0;
    for(int i = 0; i < n; i++) {
        if(a[i] != p && p) {
            upd_cost(i - l, a[i-1]);
            l = i;
        }
        p = a[i];
    }
    upd_cost(n - l, a[n-1]);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}