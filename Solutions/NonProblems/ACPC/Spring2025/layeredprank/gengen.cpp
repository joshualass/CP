#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 50000000, k = 5; i <= 1000000000; i += 50000000, k += 5) {
        cout << "gen " << i << " " << i << " " << k << " 1 > $\n";
    }

    for(int l = 2; l <= 102; l += 10) {
        for(int v = 0; v <= 10; v += 5) {
            cout << "gen 1000000000 1000000000 100 0 " << l << " " << v << " > $\n";
        }
    }

    return 0;
}
