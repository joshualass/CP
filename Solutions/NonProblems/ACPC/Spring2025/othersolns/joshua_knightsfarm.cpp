#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int x, y; cin >> x >> y;
    cout << ((x + y) % 3 == 0 && x * 2 >= y && y * 2 >= x ? "YES" : "NO") << '\n';

    return 0;
}
