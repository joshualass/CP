#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int xlo = INT_MAX, xhi = INT_MIN, ylo = INT_MAX, yhi = INT_MIN;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        xlo = min(xlo, x);
        xhi = max(xhi, x);
        ylo = min(ylo, y);
        yhi = max(yhi, y);
    }

    cout << 4 << '\n';
    cout << xlo << " " << ylo << '\n';
    cout << xhi << " " << ylo << '\n';
    cout << xhi << " " << yhi << '\n';
    cout << xlo << " " << yhi << '\n';

    return 0;
}
