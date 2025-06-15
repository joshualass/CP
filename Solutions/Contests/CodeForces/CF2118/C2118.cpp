#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll n, k; cin >> n >> k;
    vector<ll> a;
    ll res = 0;
    for(int i = 0; i < n; i++) {
        ll x; cin >> x;
        res += __builtin_popcountll(x);
        for(int j = 0; j <= 60; j++) {
            if(((x >> j) & 1) == 0) {
                a.push_back(1LL << j);
            }
        }
    }

    sort(a.begin(), a.end());

    // cout << "a : " << a << '\n';

    for(ll x : a) {
        if(k >= x) {
            k -= x;
            res++;
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