#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    map<int,int> a, b;
    int fa = 0, fb = 0;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x == -1) {
            fa++;
        } else {
            a[x]++;
        }
    }
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        if(x == -1) {
            fb++;
        } else {
            b[x]++;
        }
    }

    map<int,int> m;
    for(auto [x, c] : a) {
        for(auto [y, d] : b) {
            m[x+y] += min(c, d);
        }
    }

    a[0] = 0;
    b[0] = 0;

    int lo = max((--a.end())->first, (--b.end())->first);

    int ok = fa + fb >= n;
    for(auto [v, c] : m) {
        if(v >= lo && c + fa + fb >= n) ok = 1;
    }

    cout << (ok ? "Yes" : "No") << '\n';

    return 0;
}
