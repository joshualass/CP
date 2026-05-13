#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const ll inf = 2e18;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    ll l = 1, r = inf;

    while(l != r) {
        ll m = (l + r + 1) / 2;
        ll ops = 0;
        // cout << " zzzz m : " << m << endl;
        for(int i = 0; i < n; i++) {
            ll add = max(0LL, (m - a[i] + i) / (i + 1));
            // cout << "i : " << i << " add : " << add << endl;
            ops = min(inf, ops + add);
        }
        // cout << "m : " << m << " ops : " << ops << endl;
        if(ops <= k) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    cout << l << '\n';

    return 0;
}
