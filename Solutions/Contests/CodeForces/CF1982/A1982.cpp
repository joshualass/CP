#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;

    if(x1 > y1) {
        swap(x1,y1);
        swap(x2,y2);
    }
    if(x1 <= y1 && x2 >= y2) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}