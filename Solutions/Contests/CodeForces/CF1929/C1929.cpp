#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll getbetamt(ll spent, ll k) {
    ll l = 1, r = 1e9 + 1;
    while(l != r) {
        ll m = (l + r) / 2;
        if(m * k - (m + spent) > 0) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    // cout << "spent : " << spent << " k : " << k << " l : " << l << '\n';
    return l;
}

void solve() {
    int k, x, a; cin >> k >> x >> a;
    //at each step, we make a profit
    ll sum = 0;
    for(int i = 0; i < x + 1; i++) {
        ll bet_amt = getbetamt(sum, k);
        // cout << "i : " << i << " sum : " << sum << " bet amt : " << bet_amt << '\n';
        sum += bet_amt;
        if(sum > a) break;
    }
    cout << (sum <= a ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}