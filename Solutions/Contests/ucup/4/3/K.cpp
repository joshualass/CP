#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int g = 0, mx = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        g = gcd(x, g);
        mx = max(mx, x);
    }

    cout << (((mx / g) - n) % 3 == 0 ? "YES" : "NO") << '\n';

    return 0;
}
