#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    int b, c, h; cin >> b >> c >> h;
    cout << min(b*2-1, (c + h) * 2 + 1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int casi; cin >> casi;
    while(casi-->0) solve();
    return 0;
}
