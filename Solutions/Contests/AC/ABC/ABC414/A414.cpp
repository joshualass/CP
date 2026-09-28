
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, l, r; cin >> n >> l >> r;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if(x <= l && y >= r) res++;
    }

    cout << res << '\n';

    return 0;
}
