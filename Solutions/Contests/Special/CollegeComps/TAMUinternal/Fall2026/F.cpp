#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, s; cin >> n >> s;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    auto work = [&](int f) -> vector<ll> {
        vector<ll> res(n);
        ll cur = 0;
        map<ll,ll> p;
        for(int i = 0; i < n; i++) {
            p[cur]++;
            cur += a[i];
            res[i] = p[cur - s];
            if(i && f) res[i] += res[i-1];
        }
        return res;
    };
    
    vector<ll> p = work(0);
    reverse(a.begin(), a.end());
    vector<ll> suf = work(1);
    reverse(suf.begin(), suf.end());
    ll res = 0;
    for(int i = 0; i + 1 < n; i++) {
        res += p[i] * suf[i+1];
    }

    cout << res << '\n';

    return 0;
}
