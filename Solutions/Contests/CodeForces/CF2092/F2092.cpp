#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    ld m = 0;
    for(int i = 1; i <= n; i++) {
        m += ((ld) 1) / i;
    }

    cout << n * m * log2l(n) << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}