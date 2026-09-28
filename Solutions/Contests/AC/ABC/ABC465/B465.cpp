#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y, l, r, a, b; cin >> x >> y >> l >> r >> a >> b;

    int res = 0;
    for(int i = a; i < b; i++) {
        if(l <= i && i < r) {
            res += x;
        } else {
            res += y;
        }
    }

    cout << res << '\n';

    return 0;
}
