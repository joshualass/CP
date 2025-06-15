#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll gdc(ll x) {
    ll res = 0;
    while(x) {
        res++;
        x /= 10;
    }
    return res;
}

const ll inf = 1e17;

array<ll,2> pc[18][18][18];

void solve() {
    
    ll a, b, c; cin >> a >> b >> c;

    if(pc[a][b][c][0]) {
        cout << "Yes\n";
        cout << pc[a][b][c][0] << " " << pc[a][b][c][1] << '\n';
    } else {
        cout << "No\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(ll i = 1; i < inf; i *= 2) {
        for(ll j = 1; i * j < inf; j *= 3) {
            for(ll k = 1; i * j * k < inf; k *= 5) {
                ll a = i * k, b = j * k, c = i * j * k;
                // cout << "gdc a : " << gdc(a) << " b : " << gdc(b) << " c : " << gdc(c) << '\n';
                pc[gdc(a)][gdc(b)][gdc(c)] = {a, b};
            }
        }
    }

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}