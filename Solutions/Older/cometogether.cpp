#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int ax, ay, bx, by, cx, cy; cin >> ax >> ay >> bx >> by >> cx >> cy;
    int sum = 1;
    if((ax - bx > 0 && ax - cx > 0) || (ax - bx < 0 && ax - cx < 0)) {
        sum += min(abs(ax-bx),abs(ax-cx));
    }
    if((ay - by > 0 && ay - cy > 0) || (ay - by < 0 && ay - cy < 0)) {
        sum += min(abs(ay-by),abs(ay-cy));
    }
    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}