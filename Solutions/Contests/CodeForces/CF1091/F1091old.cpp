#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) {
        cin >> x;
        x *= 2;
    }
    string s; cin >> s;

    int phase = 0; // phase 0 = only access to ground, phase 1 = access to water also
    ll res = 0;
    ll stamina = 0;

    auto optimize_flight = [&]() -> void {
        if(phase == 0) {
            ll gtf = stamina / 2;
            res -= gtf * 5;
            res += gtf;
            stamina = 0;
        } else {
            ll stf = stamina / 2;
            res -= stf * 3;
            res += stf;
            stamina = 0;
        }
    };

    for(int i = 0; i < n; i++) {
        if(s[i] == 'G' && phase == 1) s[i] = 'L';

        if(s[i] == 'G') {
            assert(phase == 0);
            res += a[i] * 5;
            stamina += a[i];
        } else if(s[i] == 'W') {
            if(phase == 0) {
                optimize_flight();
                phase = 1;
            }
            res += a[i] * 3;
            stamina += a[i];
        } else {
            ll sub = min(a[i], stamina);
            res += a[i];
            a[i] -= sub;
            stamina -= sub;
            if(phase == 0) {
                res += a[i] * 5;
            } else {
                res += a[i] * 3;
            }
        }
    }

    optimize_flight();

    cout << res / 2 << '\n';

    return 0;
}