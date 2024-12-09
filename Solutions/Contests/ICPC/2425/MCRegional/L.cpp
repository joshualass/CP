#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int low = 0, hi = 2e5;
    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        low = max(low, l);
        hi = min(hi,r);
    }    

    if(low > hi) {
        cout << "bad news\n";
    } else {
        cout << hi - low + 1 << " " << low << '\n';
    }

    return 0;
}