#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll W, H, n; cin >> W >> H >> n;
    vector<ll> needed(60);

    for(int i = 0; i < 60; i++) {
        if((W & 1) && (H & 1)) {
            needed[i] = W + H - 1;
        } else if(W & 1) {
            needed[i] = H;
        } else if(H & 1) {
            needed[i] = W;
        }

        W /= 2;
        H /= 2;
    }

    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll c = 0;
    ll use = 0;

    // cout << needed << '\n';

    for(int i = 59; i >= 0; i--) {
        c += needed[i];
        if(i < n) {
            use += min(c, a[i]);
            c -= min(c, a[i]);
        }
        c *= 4;
        if(c > 1e17) {
            cout << "-1\n";
            return 0;
        }
    }

    if(c == 0) {
        cout << use << '\n';
    } else {
        cout << "-1\n";
    }

    // auto fillneeded = [&](auto self, ll w, ll h, ll cnt) -> void {
    //     if(w == 0 || h == 0) return;
    //     ll s = 1;
    //     int d = 0;
    //     while(s * 2 <= w && s * 2 <= h) {
    //         s *= 2;
    //         d++;
    //     }

    //     ll usew = w / s * s;
    //     ll useh = h / s * s;

    //     needed[d] += (usew / s) * (useh / h);
        
    //     self(self, w - usew * s, useh);
    //     sefl(self, w )

    // };

    return 0;
}