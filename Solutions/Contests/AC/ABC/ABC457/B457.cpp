#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<vector<ll>> a(n);
    for(auto &x : a) {
        int l; cin >> l;
        x.resize(l);
        for(auto &y : x) cin >> y;
    }

    int x, y; cin >> x >> y;
    cout << a[x-1][y-1] << '\n';

    return 0;
}
