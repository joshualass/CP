#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void solve() {
    int n; cin >> n;
    vector<ll> pref(n+1);
    for(int i = 1; i <= n; i++) {
        cin >> pref[i];
        pref[i] += pref[i-1];
    }
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll l, u; cin >> l >> u;
        l--;
        ll lo = l, hi = n - 1;
        while(hi - lo > 3) {
            ll m1 = lo + (hi - lo) / 3;
            ll m2 = lo + (hi - lo) * 2 / 3;
            ll m1races = pref[m1+1] - pref[l];
            ll m1score = m1races * u - m1races * (m1races - 1) / 2;
            ll m2races = pref[m2+1] - pref[l];
            ll m2score = m2races * u - m2races * (m2races - 1) / 2;
            if(m2score > m1score) {
                lo = m1;
            } else {
                hi = m2;
            }
        }
        pair<int,ll> ans = {-1,LLONG_MIN};
        for(int j = max(l,lo-1); j < min((ll)n,hi+2); j++) {
            ll races = pref[j+1] - pref[l];
            ll score = races * u - races * (races - 1) / 2;
            if(score > ans.second) {
                ans = {j,score};
            }
        }
        cout << ans.first + 1 << " \n"[i == q-1];
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}