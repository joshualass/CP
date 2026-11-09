#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    array<int,3> a = {};
    for(int &x : a) cin >> x;

    int l = 0, r = n;
    while(l != r) {

        int m = (l + r) / 2;

        int lo = INT_MIN, hi = INT_MAX;

        for(int i = 0; i < 3; i++) {
            int x = a[i], y = a[(i + 1) % 3];
            int dist = min((x - y + n) % n, (y - x + n) % n);
            lo = max(lo, dist - m);
            hi = min(hi, dist + m);
        }

        if(lo <= hi) {
            r = m;
        } else {
            l = m + 1;
        }
    }

    cout << l << '\n';

    return 0;
}
