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

ll solve(vector<ll> v, ll k) {
    ll ans = 0;

    for(ll bit = 60; bit >= 0; bit--) {
        ll ops = 0;
        ll num = 1LL << bit;
        ll upd = num - 1;
        for(int i = 0; i < v.size(); i++) {
            if((num & v[i]) == 0) {
                ops += num - (v[i] & upd);
            }
            if(ops > k) break;
        }
        // cout << "i : " << bit << " ops : " << ops << " num : " << num << " k : " << k << " v : " << v << '\n';
        if(ops <= k) {
            ans += num;
            for(int i = 0; i < v.size(); i++) {
                if((num & v[i]) == 0) {
                    // ops += num - (v[i] & upd);
                    v[i] = num;
                }
            }
            k -= ops;
            // cout << "upd ans : " << ans << " upd k : " << k << '\n';
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    
    vector<ll> v(n);

    for(auto &x: v) cin >> x;

    for(int i = 0; i < q; i++) {
        ll k; cin >> k;
        cout << solve(v,k) << '\n';
    }

    return 0;
}