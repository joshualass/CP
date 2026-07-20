#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll n; cin >> n;
    vector<ll> costs(30);

    auto get_ops = [&](ll num) -> ll {
        return __builtin_popcountll(num) + 63 - __builtin_clzll(num);
    };

    for(ll i = 0; i < n; i++) {
        ll x; cin >> x;
        for(ll j = 0; j < 30; j++) {
            ll min_cost = INT_MAX;
            for(ll slice = j; slice < 30; slice++) {
                ll rem = x & ((1 << slice) - 1);
                ll ops = 0;
                ll num = x;
                if(rem) {
                    ops += (1 << slice) - rem;
                    num += ops;
                }
                assert(__builtin_ctzll(num) >= slice);
                ops += get_ops(num);
                min_cost = min(min_cost, ops);
            }
            // if(j == 4) {
            //     cout << "x : " << x << " mc : " << min_cost << endl;
            // }
            costs[j] += min_cost;
        }
    }

    for(ll i = 0; i < 30; i++) {
        costs[i] -= (n - 1) * i;
    }

    // cout << "costs : " << costs << endl;

    cout << *min_element(costs.begin(), costs.end()) << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}