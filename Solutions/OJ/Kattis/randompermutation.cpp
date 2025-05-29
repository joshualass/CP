#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

signed main() {

    int n;
    cin >> n;
    ld ans = 1;
    for(int i = 0; i < n; i++){
        ans *= (ld) (n - i) / (ld) n;
        ans *= (i + 1);
    }
    cout << fixed << setprecision(15) << ans << "\n";

    return 0;
}