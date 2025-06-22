#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n; cin >> n;
    ll l = 0, r = 0, either = 0;
    for(int i = 0; i < n; i++) {
        int a, b, c; cin >> a >> b >> c;

        int left_use = max(0, min(b - c, a));
        int right_use = max(0, min(b - a, c));

        l += left_use;
        r += right_use;

        a -= left_use;
        b -= left_use + right_use;
        c -= right_use;

        either += min(a, b);

        // cout << "a : " << a << " b : " << b << " c : " << c << '\n';

    }

    // cout << "l : " << l << " r : " << r << " either : " << either << '\n';

    if(l < r) {
        ll add = min(r - l, either);
        l += add;
        either -= add;
    }
    if(r < l) {
        ll add = min(l - r, either);
        r += add;
        either -= add;
    }



    cout << min(l, r) + either / 2 << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}