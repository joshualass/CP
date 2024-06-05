#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll get_bonus(ll s, ll k, ll cycles) {
    
}

ll solve1(ll s, ll k) {
    if(k < 0) return 0;
    if(s % 10 == 2 || s % 10 == 4 || s % 10 == 6 || s % 10 == 8) {

    }
}

void solve() {  
    ll s, k; cin >> s >> k;
    ll res = 0;
    for(int i = 0; i < 6; i++) {
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