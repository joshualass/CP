#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int r, x; cin >> r >> x;
    int f;
    if(x == 1) {
        f = r >= 1600 && r <= 2999;
    } else {
        f = r >= 1200 && r <= 2399;
    }

    cout << (f ? "Yes" : "No") << '\n';

    return 0;
}
