#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int x, y; cin >> x >> y;
    if(((x + y) % 2 == 0 ? x == 0 : y == 0) || x > y) {
        cout << "NO\n";
        return;
    }

    int p = 2;
    cout << "YES\n";
    for(int i = 0; i < x - ((x + y) % 2 == 0); i++) {
        cout << "1 " << p << '\n';
        cout << p << " " << p + 1 << '\n';
        p += 2;
    }
    while(p <= x + y) cout << "1 " << p++ << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}