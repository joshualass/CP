#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, k; cin >> n >> k;
    vector<ll> p(n), d(n);
    for(ll &x : p) cin >> x;
    for(ll &x : d) cin >> x;

    auto norm = [&](ll x) -> ll {
        x %= k;
        if(x < 0) x += k;
        return x;
    };

    map<ll, set<ll>> l, r;

    for(int i = 0; i < n; i++) {
        l[norm(p[i] - d[i])].insert(p[i]);
        r[norm(p[i] + d[i])].insert(p[i]);
    }

    map<array<ll,3>, ll> global_vis;
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll _s; cin >> _s;    

        set<array<ll,3>> vis;
        int ok = 1, dir = 0;
        ll s = _s, t = 0;

        // cout << "s : " << s << " t : " << t << " dir : " << dir << '\n';

        while(1) {
            if(global_vis.count({s, t, dir})) {
                ok = global_vis[{s, t, dir}];
                break;
            }

            if(vis.count({s, t, dir})) {
                // cout << "cycle :(\n";
                ok = 0;
                break;
            }

            vis.insert({s, t, dir});

            if(dir == 0) {
                if(l[norm(s - t)].lower_bound(s) == l[norm(s - t)].end()) {
                    // cout << "cya0!\n";
                    break;
                }
                ll nx_s = *l[norm(s - t)].lower_bound(s);
                ll nx_t = norm((nx_s - s) + t);
                s = nx_s;
                t = nx_t;
                dir ^= 1;
                s--;
                t = norm(t + 1);
            } else {
                if(r[norm(s + t)].upper_bound(s) == r[norm(s + t)].begin()) {
                    // cout << "cya1!\n";
                    break;
                }
                ll nx_s = *--r[norm(s + t)].upper_bound(s);
                ll nx_t = norm((s - nx_s) + t);
                s = nx_s;
                t = nx_t;
                dir ^= 1;
                s++;
                t = norm(t + 1);
            }
        }

        for(auto st : vis) global_vis[st] = ok;

        cout << (global_vis[{_s, 0, 0}] ? "YES" : "NO") << '\n';

    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}