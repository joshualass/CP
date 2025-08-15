#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, s; cin >> n >> s;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    map<ll,ll> p;
    p[a[0]] = 0;
    for(int i = 1; i + 1 < n; i++) {
        map<ll,ll> nx;
        ll x = min(a[i], s);
        ll y = a[i] - x;

        for(auto [k, v] : p) {
            if(nx.count(y) == 0) {
                nx[y] = LLONG_MAX;
            }
            nx[y] = min(nx[y], v + k * x);
        }

        swap(x, y);

        for(auto [k, v] : p) {
            if(nx.count(y) == 0) {
                nx[y] = LLONG_MAX;
            }
            nx[y] = min(nx[y], v + k * x);
        }

        p = nx;
    }

    ll res = LLONG_MAX;
    for(auto [k, v] : p) res = min(res, v + k * a[n - 1]);
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}