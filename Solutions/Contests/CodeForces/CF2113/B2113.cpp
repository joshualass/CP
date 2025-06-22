#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    ll w, h, a, b; cin >> w >> h >> a >> b;
    ll x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;

    if(abs(x1-x2) % a == 0 && abs(y1-y2) % b == 0 || abs(x1 - x2) % a == 0 && x1 != x2 || abs(y1 - y2) % b == 0 && y1 != y2) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}