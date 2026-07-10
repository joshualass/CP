#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

void solve() {
    
    ll n; cin >> n;
    vector<ll> f(n);
    for(ll i = 0; i < n; i++) {
        ll x; cin >> x;
        f[x - 1]++;
    }

    vector<array<ll,2>> cand;

    for(ll i = 1; i <= n; i++) {
        cand.push_back({i, 0});
    }

    for(ll x : f) {
        if(x) {
            vector<array<ll,2>> nx;
            for(auto [s, cnt] : cand) {
                ll l = (s - x % s) % s;
                ll use = l;
                ll rem = x - l * (s - 1);
                if(rem < 0) continue;
                assert(rem % s == 0);
                use += rem / s;
                nx.push_back({s, cnt + use});
            }
            swap(cand, nx);
        }
    }

    ll res = 1e9;
    for(auto [s, cnt] : cand) res = min(res, cnt);

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}