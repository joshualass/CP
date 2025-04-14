#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ld l = 0, r = 5;
    while(r - l > 1e-9) {
        ld m0 = l + (r - l) / 3, m1 = l + (r - l) * 2 / 3;
        if(powl(m0,5-m0) > powl(m1,5-m1)) {
            r = m1;
        } else {
            l = m0;
        }
    }

    cout << fixed << setprecision(10) << "l : " << l << " pow : " << 5 - l << '\n';

    return 0;
}
