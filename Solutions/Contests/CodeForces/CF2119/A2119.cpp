#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int a, b, x, y; cin >> a >> b >> x >> y;

    if(x <= y && a <= b) {
        cout << (b - a) * x << '\n';
    } else if(a > b) {
        if((a ^ 1) == b) {
            cout << y << '\n';
        } else {
            cout << "-1\n";
        }
    } else {
        int xcnt = (b - a) / 2, ycnt = (b - a) / 2;

        if((b - a) & 1) {
            if(a & 1) {
                xcnt++;
            } else {
                ycnt++;
            }
        }
        cout << x * xcnt + y * ycnt << '\n';
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}