#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, f; cin >> n >> f;
    vector<vector<array<ll,2>>> ch(n);
    for(int i = 1; i < n; i++) {
        int par, t; cin >> par >> t;
        par--;
        ch[par].push_back({i, t});
    }

    auto get_cnt = [&](ll dist) -> int {
        int res = 0;
        
        // auto dfs = [&](auto self, int i, ll pt) -> ll {
        //     ll furthest = 0;
        //     for(auto [c, t] : ch[i]) {
        //         furthest = max(furthest, self(self, c, t));
        //     }
        //     if(furthest + pt > dist) {
        //         res++;
        //         return -inf;
        //     } 
        //     return furthest + pt;
        // };

        //returns {distance of the furthest node with no nearby fire station, distance of the nearest firestation}
        auto dfs = [&](auto self, int i, ll pt) -> array<ll,2> {
            ll furthest_node = 0, nearest_firestation = inf;
            for(auto [c, t] : ch[i]) {
                auto [ch_fn, ch_nfs] = self(self, c, t);
                furthest_node = max(furthest_node, ch_fn);
                nearest_firestation = min(nearest_firestation, ch_nfs);
            }
            //case everything is satisfied
            if(furthest_node <= dist - nearest_firestation) {
                return {0, nearest_firestation + pt};
            }
            //case not everything satisfied, but don't need firestation
            if(furthest_node + pt <= dist) {
                return {furthest_node + pt, nearest_firestation + pt};
            }
            res++;
            //place a fire station here
            return {0, pt};
        };

        dfs(dfs, 0, inf);

        return res;
    };

    ll l = 0, r = 1e14;
    while(l != r) {
        ll m = (l + r) / 2;
        if(get_cnt(m) <= f) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';

    return 0;
}
