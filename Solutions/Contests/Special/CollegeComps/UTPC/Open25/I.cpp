#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    sort(a.begin(), a.end());

    // ll n = 1e6;
    // vector<ll> a(n, 1e6);

    ll need = 0;
    ll res = 0;
    ll bonus = 0;

    for(ll i = 0; i < n; i++) {
        if(a[i] >= need) {
            ll extra = a[i] - need;
            res += extra * need;
            need++;
            // cout << "i : " << i << " extra : " << extra << " need : " << need << '\n';
        } else {
            bonus += a[i];
        }
    }

    res += need * bonus;

    // cout << "res : " << res << '\n';

    for(ll i = 0; i < need; i++) {
        res += i * i + 1;
    }

    cout << res - 1 << '\n';

    return 0;
}
