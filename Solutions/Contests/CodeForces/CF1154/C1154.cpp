#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll a, b, c; cin >> a >> b >> c;
    ll ans = LLONG_MIN;
    for(int i = 0; i < 7; i++) {
        ll res = LLONG_MAX;
        ll ta = a, tb = b, tc = c;
        if(i > 0) ta++;
        if(i > 1) tb++;
        if(i > 2) tc++;
        if(i > 3) ta++;
        if(i > 4) tc++;
        if(i > 5) tb++;
        if(i > 6) ta++;

        {
            ll weeks = ta / 3, rem = ta % 3;
            ll days = weeks * 7;
            if(rem == 1) {
                days += 3;
            } 
            if(rem == 2) {
                days += 6;
            }
            res = min(res, days);
        }
        {
            ll weeks = tb / 2, rem = tb % 2;
            ll days = weeks * 7 + 1;
            if(rem == 1) {
                days += 4;
            } 
            res = min(res, days);
        }
        {
            ll weeks = tc / 2, rem = tc % 2;
            ll days = weeks * 7 + 2;
            if(rem == 1) {
                days += 2;
            } 
            res = min(res, days);
        }
        // cout << "i : " << i << " res : " << res << endl;
        ans = max(ans, res - i);
    }

    cout << ans << '\n';

    return 0;
}
