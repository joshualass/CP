#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    if(n > m) {
        cout << "0\n";
        return 0;
    }

    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll res = 1;
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            res = res * abs(a[i] - a[j]) % m;
        }
    }

    cout << res << '\n';

    return 0;
}
