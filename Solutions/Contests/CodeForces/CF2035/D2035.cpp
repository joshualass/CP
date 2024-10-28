#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

ll binexp(ll base, ll power) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%MOD;
        }
        base = base*base%MOD;
        power >>= 1;
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    vector<ll> m(n);
    
    for(int i = 0; i < n; i++) {
        ll num; cin >> num;
        while(num % 2 == 0) {
            m[i]++;
            num /= 2;
        }
        a[i] = num;
    }
    //is b >= a? 
    auto isgreater = [](ll a1, ll b1, ll a2, ll b2) -> bool {
        return (ld) log2l(a1) + b1 <= (ld) log2l(a2) + b2;
    };

    vector<array<ll,2>> k;
    ll p = 0;
    for(int i = 0; i < n; i++) {
        ll cb = m[i];
        ll addm = cb;
        p += a[i];
        for(int j = (int) k.size() - 1; j >= 0; j--) {
            addm += k[j][1];
            if(isgreater(a[k[j][0]], k[j][1], a[i],  addm)) {
                while(k.size() > j) k.pop_back();
                cb = addm;
            }
        }

        if(cb) {
            k.push_back({i,cb});
        }

        ll res = p;
        for(auto [idx, m] : k) {
            res += (binexp(2,m) - 1) * a[idx];
        }
        cout << res % MOD << " \n"[i == n - 1];
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}