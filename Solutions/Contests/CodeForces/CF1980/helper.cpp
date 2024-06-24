#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while(1) {
        int x, y; cin >> x >> y;
        cout << (x ^ y) << '\n';
        if(x == -1) break;
    }

    return 0;
}