#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    auto orient = [](array<ll,4> b) -> array<ll,4> {
        array<ll,4> res = b;
        for(ll i = 0; i < 3; i++) {
            rotate(b.begin(), b.begin() + 3, b.end());
            if(b < res) res = b;
        }
        return res;
    };

    ll n; cin >> n;
    vector<array<ll,4>> a(n);
    for(auto &x : a) {
        for(auto &y : x) cin >> y;
        //orient all tiles at the beginning
        x = orient(x);    
    }

    map<array<ll,4>, ll> m;
    for(auto &x : a) m[x]++;

    ll res = 0;

    auto get_square = [&](ll i, ll j, ll idx_1, ll idx_2, ll shift) -> array<ll,4> {
        array<ll,4> b = {a[i][(idx_1 + shift) % 4], a[i][(idx_2 + shift) % 4], a[j][idx_2], a[j][idx_1]};
        reverse(b.begin(),b.end());
        return orient(b);
    };

    auto ff = [&](ll n, ll k) -> ll {
        if(n < 0 || k > n) return 0;
        ll res = 1;
        for(ll i = 0; i < k; i++) {
            res *= (n - i);
        }
        return res;
    };

    auto cnt_orientations = [&](array<ll,4> b) -> ll {
        if(b[0] == b[1] && b[1] == b[2] && b[2] == b[3]) return 4;
        if(b[0] == b[2] && b[1] == b[3]) return 2;
        return 1;
    };

    auto invert = [&](array<ll,4> b) -> array<ll,4> {
        swap(b[0],b[1]);
        swap(b[2],b[3]);
        return b;
    };

    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            if(i != j) {
                //uncount tiles i, and j
                m[a[i]]--;
                m[a[j]]--;
                //tile at the bottom is upside, so we invert it
                a[j] = invert(a[j]);
                for(ll shift = 0; shift < 4; shift++) {
                    map<array<ll,4>, ll> needed;
                    for(ll idx = 0; idx < 4; idx++) {
                        needed[get_square(i,j,idx,(idx+1)%4,shift)]++;
                    }
                    ll ways = 1;
                    for(auto [square, cnt] : needed) {
                        ways *= ff(m[square], cnt);
                        for(ll k = 0; k < cnt; k++) {
                            ways *= cnt_orientations(square);
                        }
                    }
                    res += ways;
                }
                //uninvert bottom tile
                a[j] = invert(a[j]);
                m[a[i]]++;
                m[a[j]]++;
            }
        }
    }

    cout << (res / 6) << '\n';

    return 0;
}