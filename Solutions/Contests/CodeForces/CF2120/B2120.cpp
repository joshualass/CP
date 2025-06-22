#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int n, s; cin >> n >> s;
    int res = 0;
    for(int i = 0; i < n; i++) {
        int dx, dy, x, y; cin >> dx >> dy >> x >> y;
        int in = 0;
        if(x == y && dx == dy) in = 1;
        if(x + y == s && dx != dy) in = 1;
        res += in;
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}