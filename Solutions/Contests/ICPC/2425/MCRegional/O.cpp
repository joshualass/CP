#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int issquare(int x) {
    int y = sqrt(x);
    while(y * y < x) y++;
    while(y * y > x) y--;
    return y * y == x;
}

void solve() {
    int n; cin >> n;
    int s = issquare(n);
    int o = (n & 1);
    if(s || o) {
        if(o) cout << 'O';
        if(s) cout << 'S';
        cout << '\n';
    } else {
        cout << "EMPTY\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}