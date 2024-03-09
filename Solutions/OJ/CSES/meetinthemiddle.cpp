#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, x; cin >> n >> x;
    unordered_map<ll,ll> m;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    ll first = n / 2;
    ll second = n - first;
    for(ll i = 0; i < (1 << first); i++) {
        ll num = i;
        ll cnt = 0;
        for(ll j = 0; j < first; j++) {
            if((num >> j) & 1) {
                cnt += v[j];
            }
        }
        if(m.find(cnt) == m.end()) {
            m[cnt] = 1;
        } else {
            m[cnt]++;
        }
    }

    v.erase(v.begin(), v.begin() + first);
    ll ans =0;
    for(ll i = 0; i < (1 << second); i++) {
        ll num = i;
        ll cnt = 0;
        for(ll j = 0; j < second; j++) {
            if((num >> j) & 1) {
                cnt += v[j];
            }
        }
        if(m.find(x-cnt) != m.end()) {
            ans += m[x-cnt];
        }
    }
    cout << ans << "\n";
    return 0;
}