#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    int a, x, y; cin >> a >> x >> y;
    if(x > y) swap(x, y);
    cout << (x < a && a < y ? "NO" : "YES") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}