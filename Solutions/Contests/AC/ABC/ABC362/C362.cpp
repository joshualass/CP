#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<array<ll,2>> a(n);
    
    ll lo = 0, hi = 0;
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        lo += a[i][0];
        hi += a[i][1];
    }

    if(hi >= 0 && lo <= 0) {
        cout << "Yes\n";
        ll extra = -lo;
        for(int i = 0; i < n; i++) {
            ll e = min(extra, a[i][1] - a[i][0]);
            extra -= e;
            ll amt = a[i][0] + e;
            cout << amt << " \n"[i == n - 1];
        }
    } else {
        cout << "No\n";
    }

    return 0;
}