#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll rotateOne(ll &x, ll &y) {
    y = -y;
    swap(x,y);
}

ll rotateCC(ll &xa, ll &ya, ll &xb, ll &yb, ll &xc, ll &yc) {
    rotateOne(xa,ya);
    rotateOne(xb,yb);
    rotateOne(xc,yc);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll xa, ya, xb, yb, xc, yc; cin >> xa >> ya >> xb >> yb >> xc >> yc;
    // ll moves = abs(xa-xb) - 1 + abs(ya-yb) - 1 + abs(xb-xc) - 1 + abs(yb-yc) - 1;
    ll moves = 0;
    if(xa != xb) {
        moves += abs(xa-xb) - 1;
    }
    if(ya != yb) {
        moves += abs(ya-yb) - 1;
    }
    if(xb != xc) {
        moves += abs(xb-xc) - 1;
    }
    if(yb != yc) {
        moves += abs(yb-yc) - 1;
    }
    if(xa == xb) {
        
    }

    return 0;
}