#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int M, D, y, m, d; cin >> M >> D >> y >> m >> d;

    if(D == d) {
        if(M == m) {
            cout << y + 1 << " 1 1\n";
        } else {
            cout << y << " " << m + 1 << " 1\n";
        }
    } else {
        cout << y << " " << m << " " << d + 1 << '\n';
    }

    return 0;
}