#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const ll inf = 1e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll _n, _w; cin >> _n >> _w;
    vector<ll> _a(_n);
    for(ll &x : _a) cin >> x;

    lll n = _n, w = _w;
    vector<lll> a(n);
    for(int i = 0; i < n; i++) a[i] = _a[i];

    sort(a.rbegin(), a.rend());

    auto check = [&](lll pours) -> int {
        // cout << "pours : " << (ll) pours << endl;
        
        //case where we pour everytime from largest
        {
            lll poured = a[0] * pours;
            lll ge = poured + a[0];
            lll le = w - poured;    
            if(ge >= le) return 1;
        }

        lll start = pours * a[0];
        lll sum = 0, ssum = 0;

        for(int i = 1; i < min(n, pours); i++) {
            ssum += sum;
            sum += a[i];
            
            lll ge = start + sum;
            lll le = w - (start * (i) + (start - a[0]) + ssum);
            // cout << "ge : " << (ll) ge << " le : " << (ll) le << endl;
            
            if(ge >= le) return 1;
            
            start -= a[0];
        }

        return 0;

    };

    lll l = 1, r = inf;
    while(l != r) {
        lll m = (l + r) / 2;
        if(check(m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << (ll) l << '\n';

    return 0;
}
