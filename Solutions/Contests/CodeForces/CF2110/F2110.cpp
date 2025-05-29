#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    vector<ll> b;

    auto f = [&](ll x, ll y) -> ll {
        if(x == 0 || y == 0) return 0;
        return x % y + y % x;
    };

    ll res = 0, mx = 0;
    for(ll i = 0; i < n; i++) {
        if(a[i] >=  mx * 2) {
            for(ll j = 0; j < i; j++) {
                res = max(res, f(a[j], a[i]));
            }
        }
        // cout << "i : " << i << " res : " << res << " mx : " << mx << '\n';
        res = max(res, f(a[i], mx));
        mx = max(mx, a[i]);
        cout << res << " \n"[i == n - 1];
        b.push_back(res);
    }

}

vector<ll> solve(vector<ll> a) {
    
    ll n = a.size();
    vector<ll> b;

    auto f = [&](ll x, ll y) -> ll {
        if(x == 0 || y == 0) return 0;
        return x % y + y % x;
    };

    ll res = 0, mx = 0;
    for(ll i = 0; i < n; i++) {
        if(a[i] > mx * 2) {
            for(ll j = 0; j < i; j++) {
                res = max(res, f(a[j], a[i]));
            }
        }
        // cout << "i : " << i << " res : " << res << " mx : " << mx << '\n';
        res = max(res, f(a[i], mx));
        mx = max(mx, a[i]);
        b.push_back(res);
    }

    return b;

}

vector<ll> solve_slow(vector<ll> a) {
    vector<ll> res(a.size());
    ll ans = 0;
    ll n = a.size();
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j <= i; j++) {
            ans = max(ans, a[i] % a[j] + a[j] % a[i]);
        }
        res[i] = ans;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // ll n, it, mx; cin >> n >> it >> mx;
    // for(ll i = 0; i < it; i++) {
    //     vector<ll> a(n);
    //     for(ll &x : a) x = rng() % mx + 1;
    //     if(solve(a) != solve_slow(a)) {
    //         cout << "failure a : " << a << '\n';
    //     }
    // }

    // cout << "all ok!\n";

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}