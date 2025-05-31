#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll hi = ((ll) 1e9) + 1;

void solve() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    auto get = [&](ll x, ll nx) -> ll {
        ll p1 = 0;
        ll p2 = __builtin_ctz(x);
        while(x % 2 == 0 && x / 2 != nx) {
            x >>= 1;
            p1++;
        }
        return (1 << p2) - ((1 << (p2 - p1)) - 1);
    };

    vector<ll> p(n), s(n);
    for(ll i = 0; i < n; i++) {
        if(i) p[i] += p[i-1];
        ll nx = (i == n - 1 ? hi : a[i+1]);
        p[i] += get(a[i], nx);
    }

    for(ll i = n - 1; i >= 0; i--) {
        if(i != n - 1) s[i] += s[i+1];
        ll nx = (i ? a[i-1] : hi);
        s[i] += get(a[i], nx);
    }

    ll ok = 0;
    for(ll i = 0; i < n; i++) {
        ll t = (i ? p[i-1] : 0) + (i == n - 1 ? 0 : s[i+1]) + get(a[i], hi);
        if(t >= k) ok = 1;
    }

    cout << (ok ? "Yes" : "No") << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const int hi = ((int) 1e9) + 1;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
    
//     int n, k; cin >> n >> k;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     vector<vector<int>> p(n, vector<int>(30)), s(n, vector<int>(30));

//     auto get = [&](int x, int nx) -> int {
//         int res = 0;
//         while(x % 2 == 0 && x / 2 != nx) {
//             res++;
//             x /= 2;
//         }
//         return res;
//     };

//     for(int i = 0; i < n; i++) {
//         if(i) p[i] = p[i-1];
//         int nx = (i == n - 1 ? hi : a[i+1]);
//         p[i][get(a[i], nx)]++;
//     }

//     for(int i = n - 1; i >= 0; i--) {
//         if(i < n - 1) s[i] = s[i+1];
//         int nx = (i ? a[i-1] : hi);
//         s[i][get(a[i], nx)]++;
//     }

//     int ok = 0;
//     for(int i = 0; i < n; i++) {
//         vector<int> lhs = (i ? p[i-1] : vector<int>(30, 0)), rhs(i == n - 1 ? vector<int>(30, 0) : s[i+1]);
//         // cout << "i : " << i << " lhs : " << lhs << '\n';
//         for(int j = 0; j < 30; j++) lhs[j] += rhs[j];
//         lhs[0] += 1 << get(a[i], hi);
//         int t = k;
//         // cout << "starting lhs : " << lhs << '\n';
//         for(int j = 29; j >= 0; j--) {
//             int ops = min(lhs[j], t >> j);
//             t -= ops << j;
//             lhs[j] -= ops;
//             if(j) lhs[j-1] += lhs[j];
//         }
//         if(t == 0) {
//             ok = 1;
//             // cout << "ok i : " << i << "\n";    
//         }

//     }

//     cout << (ok ? "Yes" : "No") << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }