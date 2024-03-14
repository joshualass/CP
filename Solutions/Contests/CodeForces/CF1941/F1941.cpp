#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

ll findmc(vector<ll> v, ll i) {
    set<ll> s(v.begin(), v.end());
    s.insert(i);
    vector<ll> a(s.begin(),s.end());
    ll md = 0;
    for(int i = 0; i < a.size() - 1; i++) {
        md = max(md, a[i+1]-a[i]);
    }
    return md;
}

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<ll> a(n), d(m);
    set<ll> f;
    for(ll &x : a) cin >> x;
    for(ll &x : d) cin >> x;
    for(int i = 0; i < k; i++) {
        ll num; cin >> num;
        f.insert(num);
    }
    ll md = 0;
    for(int i = 1; i < n - 1; i++) {
        if(a[i+1] - a[i] > a[md+1] - a[md]) md = i;
    }

    ll t = (a[md] + a[md+1]) / 2;
    // cout << "t : " << t << '\n';
    ll cl = INT_MIN, cu = INT_MAX;
    for(ll x : d) {
        if(f.lower_bound(t - x) != f.begin()) {
            cl = max(cl, x + (*--f.lower_bound(t-x)));
        }
        if(f.lower_bound(t - x) != f.end()) {
            cu = min(cu, x + (*f.lower_bound(t-x)));
        }
    }
    // cout << "cl : " << cl << " cu : " << cu << '\n';
    cout << min({findmc(a,cl),findmc(a,cu),a[md+1] - a[md]}) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}