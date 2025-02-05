#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ld sa = 0, sb = 0;
    for(int i = 0; i < n; i++) {
        ld a, b; cin >> a >> b;
        sa += a;
        sb += b;
    }

    if(sb / sa / 60 <= 1.00000000001) {
        cout << "measurement error\n";
        return 0;
    }

    cout << fixed << setprecision(10) << sb / sa / 60 << '\n';

    return 0;
}