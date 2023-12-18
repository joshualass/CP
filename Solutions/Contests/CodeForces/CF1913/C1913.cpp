#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<ll> v(32);

    for(ll i = 0; i < n; i++) {
        int type; cin >> type;
        if(type == 1) {
            ll x; cin >> x;
            v[x]++;
        } else if(type == 2) {
            // cout << v << "\n";
            ll val; cin >> val;
            vector<ll> copy = v;
            bool ok = 1;
            for(ll i = 31; i >= 0; i--) {
                if((val >> i) & 1) {
                    bool found = 0;
                    ll needed = 1;
                    for(int j = i; j >= 0; j--) {
                        // if(copy[j] >= needed) {
                        //     // cout << "i : " << i << " j : " << j << " needed : " << needed << '\n';
                        //     copy[j] -= needed;
                        //     found = 1;
                        //     break;
                        // }
                        ll remove = min(copy[j], needed);
                        copy[j] -= remove;
                        needed -= remove;
                        needed *= 2;
                    }
                    if(needed != 0) {
                        ok = 0;
                    }
                }
            }
            cout << (ok ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}