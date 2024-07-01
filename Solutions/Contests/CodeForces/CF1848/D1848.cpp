#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll get_bonus(ll s, ll k, ll cycles) {
    s += 20 * cycles;
    k -= cycles * 4;
    return s * k;
}

ll solve1(ll s, ll k) {
    if((s & 1) || s % 10 == 0) return s * k;
    ll cycles = k / 4;
    ll l = 0, r = cycles;
    while(r - l > 10) {
        ll m1 = l + (r - l) / 3;
        ll m2 = l + (r - l) * 2 / 3;
        ll v1 = get_bonus(s,k,m1);
        ll v2 = get_bonus(s,k,m2);
        if(v1 > v2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ll res = 0;
    for(int i = l; i <= r; i++) {
        res = max(res,get_bonus(s,k,i));
    }
    return res;
}

void solve() {  
    ll s, k; cin >> s >> k;
    ll res = s * k;
    for(int i = 0; i < 6 && k > 0; i++) {
        // cout << "s : " << s << " k : " << k << " s1 : " << solve1(s,k) << '\n';
        res = max(res, solve1(s,k));
        s += s % 10;
        k--;
    }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}