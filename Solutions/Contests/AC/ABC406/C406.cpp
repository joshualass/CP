#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    ll res = 0;
    set<int> pk, va;
    for(int i = 1; i + 1 < n; i++) {
        if(a[i] > a[i-1] && a[i] > a[i+1]) {
            pk.insert(i);
        }
        if(a[i] < a[i-1] && a[i] < a[i+1]) {
            va.insert(i);
        }
    }

    for(int p : pk) {
        int nxv = (va.upper_bound(p) == va.end() ? n - 1 : *va.upper_bound(p));
        int nxp = (pk.upper_bound(nxv) == pk.end() ? n - 1 : *pk.upper_bound(nxv));
        int pvv = (va.lower_bound(p) == va.begin() ? 0 : *--va.lower_bound(p));

        // cout << "pvv : " << pvv << " p : " << p << " nxv : " << nxv << " nxp : " << nxp << "\n";

        res += 1LL * (p - pvv) * (nxp - nxv);

    }

    cout << res << '\n';

    return 0;
}
