#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    ll n, k, x, y; cin >> n >> k >> x >> y;
    for(int i = 1; i <= k; i++) {
        int xc = (((n - i) % x) == 0 && i + x >= k);
        int yc = (((n - i) % y) == 0 && i + y >= k);
        cout << (xc != yc);
    }

    cout << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}