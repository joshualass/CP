#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    ll ops = 0;
    for(int i = 0; i < n; i++) {
        ll h; cin >> h;

        ops += h / 5 * 3;

        h -= h / 5 * 5;

        while(h > 0) {
            ops++;
            h -= (ops % 3 == 0 ? 3 : 1);
        }

    }

    cout << ops << '\n';

    return 0;
}