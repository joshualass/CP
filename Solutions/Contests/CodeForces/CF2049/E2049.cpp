#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

ll debug = 0;


void solve() {
    
    ll n;
    ll pos, k;
    if(debug == 0) {
        cin >> n;
    } else {
        n = 1 << (rng() % 29 + 2);
        // n = 16;
        k = rng() % (n - 2) + 2;
        pos = rng() % n;
        // k = 2, pos = 1;
    }

    ll n4 = n >> 2;
    ll inv = 0, toggle = 0, os = 0;
    
    auto ask = [&](ll l, ll r) -> ll {
        if(os) {
            l += n4;
            r += n4;
            ll sub = max(0LL, r - n);
            l -= sub;
            r -= sub;
        }
        if(inv) {
            l = n - l;
            r = n - r;
            swap(l, r);
        } 
        ll res; 
        if(debug == 0) {
            cout << "? " << l + 1 << " " << r << endl;
            cin >> res;
        } else {
            if(!(0 <= l && l <= r && r <= n)) {
                cout << "WA n : " << n << " k : " << k << " pos : " << pos << endl;
                cout << "l : " << l << " r : " << r << endl;
                assert(0);
            }
            res = (l <= pos && pos < r) ^ ((r - l) >= k);
        }
        res ^= toggle;
        // cout << "ask l : " << l << " r : " << r << " res : " << res << endl;
        return res;
    };

    ll a = ask(0, n4), b = ask(n4, n4 * 2), c = ask(n4 * 2, n4 * 3);

    ll zc = (a == 0) + (b == 0) + (c == 0);
    ll oc = 3 - zc;

    ll l, r;

    if(zc > oc) {
        //we are telling the truth => k < 2^{n - 2}
        l = n4 + 1, r = n - 1;
        if(a == 0 && b == 0) {
            inv = 1;
        }
        toggle = 1;
        if(b != c) {
            os = 1;
        }
    } else {
        l = 2, r = n4;
        if(a == 0 || b == 0) {
            inv = 1;
        }
    }
    

    ll il = l, ir = r;

    while(l != r) {
        ll m = (l + r) / 2;
        if(ask(0, m)) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    if(debug == 0) {
        cout << "! " << l << endl;
    } else {
        if(l != k) {
            cout << "WA n : " << n << " k : " << k << " pos : " << pos << endl;
            cout << "a : " << a << " b : " << b << " c : " << c << endl;
            cout << "l : " << l << " k : " << k << endl;
            cout << "init l : " << il << " init r : " << ir << endl;
            cout << "inv : " << inv << " toggle : " << toggle << " os : " << os << endl;
            assert(0);
        }
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        ll casi; cin >> casi;
        while(casi-->0) solve();
    } else {
        for(ll i = 0; i < 1000; i++) {
            solve();
        }
    }


    return 0;
}