#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    ll n, c; cin >> n >> c;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> m(n+1);
    for(int i = n - 1; i >= 0; i--) {
        m[i] = max(m[i+1],a[i]);
    }

    ll f = 0;
    for(int i = 0; i < n; i++) {
        if(i == 0) {
            if(a[i] + c >= m[i+1]) {
                cout << 0;
            } else {
                cout << 1;
            }
            f = a[i] + c;
        } else {
            if(a[i] >= m[i+1] && a[i] > f) {
                cout << 0;
            } else {
                if(c + a[i] >= m[i+1]) {
                    cout << i;
                } else {
                    cout << i + 1;
                }
            }
            f = max(f, a[i]);
        }

        c += a[i];

        cout << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}