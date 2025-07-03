#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<array<int,2>, int> m;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        int g = gcd(x,y);
        m[{x/g,y/g}]++;
        res = max(res,m[{x/g,y/g}]+m[{-x/g,-y/g}]);
    }
    cout << res << '\n';
    return 0;
}