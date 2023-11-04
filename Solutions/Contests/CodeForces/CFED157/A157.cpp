#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void solve() {
    int x, y, k; cin >> x >> y >> k;
    if(x >= y) {
        cout << x << '\n';
    } else {
        int dist = min(y, x + k);
        cout << dist + (y - dist) * 2 << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}