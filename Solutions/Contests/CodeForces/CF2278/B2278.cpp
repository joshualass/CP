#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

void solve() {
    
    int x, y, z; cin >> x >> y >> z;
    char c;

    if(x >= y && x >= z) {
        c = 'P';
    } else if(y >= x && y >= z) {
        c = 'R';
    } else {
        c = 'S';
    }

    cout << string(x + y + z, c) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}