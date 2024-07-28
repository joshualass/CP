#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll findmax(ll lo, ll loc, ll hic, ll k) {
    ll hi = lo + 1;

    ll loplace = min(loc, k / lo);
    ll remain = k - loplace * lo;
    ll hiplace = min(hic, remain / hi);
    ll remain2 = remain - hi * hiplace;

    ll hiextra = min({loplace, remain2, hic - hiplace});

    return loplace * lo + hiplace * hi + hiextra;

}

void solve() {
    ll n, m; cin >> n >> m;
    map<ll,ll> f;
    vector<int> a(n);
    // for(int &x : a) cin >> x;
    for(int i = 0; i < n; i++) {
        int c; cin >> c;
        // f[a[i]] += c;
        f[c]++;
    }

    ll res = 0;
    for(auto [u, v] : f) {
        if(f.count(u + 1)) {
            res = max(res, findmax(u,v,f[u+1], m));
        } else {
            res = max(res, findmax(u,v,0,m));
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