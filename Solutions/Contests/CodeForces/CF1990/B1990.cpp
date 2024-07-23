#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {

    int n, x, y; cin >> n >> x >> y;
    x--; y--;
    for(int i = 0; i < n; i++) {

        if(i < y) {
            if((y - i) & 1) {
                cout << -1;
            } else {
                cout << 1;
            }
        } else if(i >= y && i <= x) {
            cout << 1;
        } else {
            if((i - x) & 1) {
                cout << -1;
            } else {
                cout << 1;
            }
        }
        cout << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}