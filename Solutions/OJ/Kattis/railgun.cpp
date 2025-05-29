#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {

    int n; cin >> n;
    vector<array<ll,2>> a(n);

    for(auto &x : a) {
        for(auto &y : x) cin >> y;
    }   

    a.push_back({0, 0});
    n++;

    auto work = [&](vector<array<ll,2>> a) -> ll {

        sort(a.begin(), a.end());

        ll mx = 0, mn = 0, nmx = 0, nmn = 0;
        vector<ll> pmax(n), pmin(n), smax(n), smin(n);

        for(int i = 0; i < n; i++) {

            if(i && a[i][0] != a[i-1][0]) {
                mx = max(mx, nmx);
                mn = min(mn, nmn);
            }

            pmax[i] = mx;
            pmin[i] = mn;

            nmx = max(nmx, a[i][1]);
            nmn = min(nmn, a[i][1]);
        }

        mx = 0, mn = 0, nmx = 0, nmn = 0;

        for(int i = n - 1; i >= 0; i--) {

            if(i != n - 1 && a[i][0] != a[i+1][0]) {
                mx = max(mx, nmx);
                mn = min(mn, nmn);
            }

            smax[i] = mx;
            smin[i] = mn;

            nmx = max(nmx, a[i][1]);
            nmn = min(nmn, a[i][1]);
        }

        auto get_cost = [&](int lidx, int ridx) -> ll {
            ll need_up = max(pmax[lidx], smax[ridx]);
            ll need_down = min(pmin[lidx], smin[ridx]);
            return a[ridx][0] * 2 - a[lidx][0] + need_up * 2 - need_down;
            // return abs(a[ridx][0] * 2) + abs(a[lidx][0]) + min(need_up, need_down) * 2 + max(need_up, need_down);
        };

        ll res = LLONG_MAX;

        //do all ranges inclusively 
        auto dfs = [&](auto self, int xll, int xlr, int xrl, int xrr) -> void {
            if(xrl > xrr) return;
            int m = (xrl + xrr) / 2;

            int best_idx = -1;
            ll best_cost = LLONG_MAX;
            for(int i = xll; i <= xlr; i++) {
                ll cost = get_cost(i, m);
                if(cost < best_cost) {
                    best_idx = i;
                    best_cost = cost;
                }
            }

            res = min(res, best_cost);

            self(self, xll, best_idx, m + 1, xrr);
            self(self, best_idx, xlr, xrl, m - 1);
        };

        int xlr = 0, xrl = n - 1;
        while(xlr + 1 < n && a[xlr+1][0] <= 0) xlr++;
        while(xrl > 0 && a[xrl-1][0] >= 0) xrl--;

        // dfs(dfs, 0, n - 1, 0, n - 1);
        // cout << "xlr : " << xlr << " xrl : " << xrl << '\n';
        dfs(dfs, 0, xlr, xrl, n - 1);

        return res;

    };

    ll res = LLONG_MAX;

    for(int i = 0; i < 4; i++) {

        res = min(res, work(a));
        for(auto &x : a) x[1] *= -1;
        if(i == 1) {
            for(auto &x : a) x[0] *= -1;
        }

    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}