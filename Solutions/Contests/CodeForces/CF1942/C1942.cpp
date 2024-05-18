#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    ll n, x, y; cin >> n >> x >> y;

    vector<ll> a(x);
    for(ll &y : a) cin >> y;
    sort(a.begin(), a.end());
    vector<ll> d;
    a.push_back(a.front() + n);
    for(int i = 0; i < x; i++) {
        d.push_back(a[i+1] - a[i]);
    }
    sort(d.begin(), d.end(), [] (ll &lhs, ll &rhs) -> bool {
        if((lhs & 1) == (rhs & 1)) {
            return lhs < rhs;
        } else if(lhs & 1) {
            return 0;
        } else {
            return 1;
        }
    });

    // cout << "d : " << d << '\n';

    ll res = d.size() - 2;
    for(int i = 0; i < d.size(); i++) {
        ll needed = (d[i] - 1) / 2;
        if(y >= needed) {
            res += d[i] - 1;
            y -= needed;
        } else {
            res += y * 2;
            break;
        }
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