#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    int n, q; cin >> n >> q;
    vector<array<ll,2>> a(n); // {position, utility}
    for(auto &x : a) cin >> x[0];
    for(auto &x : a) cin >> x[1];
    vector<array<ll,2>> qs(q);
    for(auto &x : qs) for(auto &y : x) cin >> y;
    
    auto dis = [&](array<ll,2> f, array<ll,2> s) -> ld {
        auto [x1, y1] = f;
        auto [x2, y2] = s;
        return sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    };
    
    for(int i = 0; i < q; i++) {
        ld res = LLONG_MIN;
        for(int j = 0; j < n; j++) {
            res = max(res, a[j][1] - dis(qs[i], array<ll,2>{a[j][0], 0}));
        }
        cout << fixed << setprecision(10) << res << " \n"[i == q - 1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}
