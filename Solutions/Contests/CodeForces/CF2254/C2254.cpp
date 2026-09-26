#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

void solve() {
    
    ll n; cin >> n;
    string a, b; cin >> a >> b;

    auto work = [](string a, string b) -> ll {
        vector<ll> c, d;
        for(ll i = 0; i < sz(a); i++) {
            if(a[i] == '0') c.push_back(i);
            if(b[i] == '0') d.push_back(i);
        }
        if(sz(c) != sz(d)) return 1e18;
        ll res = 0;
        for(ll i = 0; i < sz(c); i++) res += abs(c[i] - d[i]);
        return res;
    };

    auto chop = [](string s) -> array<string,2> {
        array<string,2> res = {};
        for(ll i = 0; i < sz(s); i++) {
            res[i & 1].push_back(s[i]);
        }
        return res;
    };

    array<string,2> achop = chop(a), bchop = chop(b);
    ll res = work(achop[0], bchop[0]) + work(achop[1], bchop[1]);
    cout << (res >= 1e18 ? "NO" : "YES") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    for(ll i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}