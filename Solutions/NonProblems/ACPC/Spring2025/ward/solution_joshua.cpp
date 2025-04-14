#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int lox = INT_MAX, loy = INT_MAX, hix = INT_MIN, hiy = INT_MIN;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        lox = min(x, lox);
        loy = min(y, loy);
        hix = max(x, hix);
        hiy = max(y, hiy);
    }

    cout << max(hix - lox, hiy - loy) + 1 << '\n';

    return 0;
}
