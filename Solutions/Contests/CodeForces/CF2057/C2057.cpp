#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int l, r; cin >> l >> r;
    int a = 0, b = 0;
    for(int bit = 29; bit >= 0; bit--) {
        a += r & (1 << bit);
        b += r & (1 << bit);
        if(((l >> bit) & 1) != ((r >> bit) & 1)) {
            b--;
            break;
        }
    }
    int c;
    if(a + 1 <= r) {
        c = a + 1;
    } else {
        c = b - 1;
    }
    cout << a << " " << b << " " << c << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}