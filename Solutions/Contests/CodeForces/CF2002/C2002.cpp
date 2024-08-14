#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;


//thank god no geometry
void solve() {
    int n; cin >> n;

    vector<array<ll,2>> pts;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pts.push_back({x,y});
    }

    ll xs, ys, xt, yt; cin >> xs >> ys >> xt >> yt;
    ll dist = (xs - xt) * (xs - xt) + (ys - yt) * (ys - yt);

    bool ok = 1;
    for(int i = 0; i < n; i++) {
        ll d = (pts[i][0] - xt) * (pts[i][0] - xt) + (pts[i][1] - yt) * (pts[i][1] - yt);
        if(d <= dist) ok = 0;
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}