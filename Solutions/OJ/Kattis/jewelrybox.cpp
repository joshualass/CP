#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ld eps = 1e-9;

void solve() {
    
    int x, y; cin >> x >> y;
    
    ld lo = 0, hi = ((ld) min(x,y)) / 2;

    auto ga = [&](ld h) -> ld {
        return h * (x - h * 2) * (y - h * 2);
    };

    while(hi - lo > eps) {
        ld m1 = lo + (hi - lo) / 3;
        ld m2 = lo + (hi - lo) / 3 * 2;
        ld a1 = ga(m1), a2 = ga(m2);
        if(a1 > a2) {
            hi = m2;
        } else {
            lo = m1;
        }
    }

    cout << fixed << setprecision(10) << ga((lo + hi) / 2) << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}