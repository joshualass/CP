// https://codeforces.com/contest/1578/problem/D
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

pair<ll,ll> dragon_curve(ll x, ll y) {
    ll bit = 1, pos = 0;
    while(!(-1 <= x && x <= 0 && -1 <= y && y <= 0)) {
        // cout << "x: " << x << " y: " << y << '\n';
        bit <<= 1;
        if((x ^ y ^ (x ^ y) >> 1) & 1) {
            pos = bit - 1 - pos;
        }
        if(((x ^ y) >> 1) & 1) {
            ll newx = (x >> 1) + (y + 1 >> 1);
            ll newy = (y + 1 >> 1) - (x >> 1) - 1;
            // cout << "newx1: " << newx << " newy1: " << newy << '\n';
            x = newx;
            y = newy;
        } else {
            ll newx = (x + 1 >> 1) + (y >> 1);
            ll newy = (y >> 1 ) - (x + 1 >> 1);
            // cout << "newx2: " << newx << " newy2: " << newy << '\n';
            x = newx;
            y = newy;
        }
    }
    return {(x & 1 ^ y & 3) + 1, pos + 1};
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int casi; cin >> casi;

    while(casi-->0) {
        ll x, y; cin >> x >> y;
        pair<ll,ll> ans = dragon_curve(x,y);
        cout << ans.first << " " << ans.second << '\n';
    }

    return 0;
}