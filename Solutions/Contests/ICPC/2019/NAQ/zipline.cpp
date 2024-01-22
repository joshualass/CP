#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ld ep = 1e-10;

ld dist(ld x, ld y) {
    return sqrt(x * x + y * y);
}

ld find_length(ld w, ld h1, ld h2, ld r, ld m) {
    ld l1 = dist(m,h1-r);
    ld l2 = dist(w - m, h2-r);
    return l1 + l2;
}

void solve() {
    ld w, h1, h2, R; cin >> w >> h1 >> h2 >> R;

    ld l = 0, r = w;
    while(r - l > ep) {
        ld m1 = l + (r - l) / 3;
        ld m2 = l + (r - l) / 3 * 2;

        ld l1 = find_length(w, h1, h2, R, m1);
        ld l2 = find_length(w, h1, h2, R, m2);

        if(l1 < l2) {
            r = m2;
        } else {
            l = m1;
        }

    }

    cout << dist(w,abs(h1-h2)) << " " << find_length(w, h1, h2, R, l) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed << setprecision(15);
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}