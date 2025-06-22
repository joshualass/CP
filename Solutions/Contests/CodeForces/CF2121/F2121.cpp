#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll n, s, x; cin >> n >> s >> x;

    map<ll,ll> m, to_add;
    ll rc = 0, res = 0;

    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        to_add[rc]++;
        rc += a;
        if(a > x) {
            m.clear();
            to_add.clear();
        }
        if(a == x) { 
            for(auto [k, v] : to_add) m[k] += v;
            to_add.clear();
        }
        res += m[rc - s];

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