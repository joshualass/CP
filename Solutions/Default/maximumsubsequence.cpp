#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, m; cin >> n >> m;
    set<ll> s;
    vector<ll> v(n);
    for(ll &x: v) cin >> x;
    ll first = n / 2;
    for(int i = 0; i < (1 << first); i++) {
        ll num = i;
        ll cnt = 0;
        for(int j = 0; j < first; j++) {
            if((num >> j) & 1) {
                cnt += v[j];
            }
        }
        s.insert(cnt % m);
    }
    v.erase(v.begin(),v.begin()+first);
    first = v.size();
    ll ans = 0;
    for(int i = 0; i < (1 << first); i++) {
        ll num = i;
        ll cnt = 0;
        for(ll j = 0; j < first; j++) {
            if((num >> j) & 1) {
                cnt += v[j];
            }
        }
        cnt %= m;
        ll search = ((2 * m) - cnt - 1) % m;
        if(s.size() && s.upper_bound(search) != s.begin()) {
            ll best = *(--s.upper_bound(search));
            ans = max(ans, cnt + best);
        } else {
            ans = max(ans, cnt);
        }
    }
    cout << ans << "\n";
    return 0;
}