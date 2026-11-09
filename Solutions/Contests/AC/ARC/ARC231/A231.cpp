#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll inf = 1e18;

void solve() {
    
    int n; cin >> n;
    vector<array<ll,3>> a(n);
    vector<ll> p(n + 1);

    for(int i = 0; i < n; i++) {
        for(auto &x : a[i]) cin >> x;
        p[i+1] = p[i] + a[i][2];
    }

    vector<vector<ll>> b(500, vector<ll>(500, inf));
    ll res = inf;
    auto upd = [&](int x, int y, int time, ll cost) -> void {
        // cout << "x : " << x << " y : " << y << " time : " << time << " cost : " << cost << endl;
        res = min(res, cost + p[n] - p[time]);
        for(int i = 0; i < 500; i++) {
            b[x][i] = min(b[x][i], cost + (p[n] - p[time]) + (y - i) * (y - i));
        }
    };

    upd(0, 0, 0, 0);

    for(int i = 0; i < n; i++) {
        int time = i + 1;
        auto [x, y, z] = a[i];
        ll best_prev = inf;
        for(int j = 0; j < 500; j++) {
            best_prev = min(best_prev, b[j][y] - (p[n] - p[i]) + (x - j) * (x - j));
        }
        upd(x, y, time, best_prev);
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}