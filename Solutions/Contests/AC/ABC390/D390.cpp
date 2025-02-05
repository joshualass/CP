#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    vector<ll> s;
    int ct = 0;

    // auto dfs = [&](auto self, vector<ll> b, ll c, ll x, int p) -> void {
    //     if(p == b.size()) {
    //         x ^= c;
    //         if(b.size() == 0) {
    //             ct++;
    //             s.push_back(x);
    //             return;
    //         }
    //         c = b[0];
    //         p = 0;
    //         b.erase(b.begin() + p);
    //         self(self, b, c, x, p);
    //         return;
    //     }
    //     self(self, b, c, x, p + 1);
    //     c += b[p];
    //     b.erase(b.begin() + p);
    //     self(self, b, c, x, p);
    // };

    // dfs(dfs, a, 0, 0, n);

    // auto dfs = [&](auto self, vector<ll> &b, ll x) -> void {
    //     if(b.size() == 0) {
    //         s.push_back(x);
    //         return;
    //     }
    //     for(int bm = 0; bm < (1 << (b.size() - 1)); bm++) {
    //         int tbm = 1 + (bm << 1);
    //         vector<ll> r;
    //         ll c = 0;
    //         for(int i = b.size() - 1; i >= 0; i--) {
    //             if((tbm >> i) & 1) {
    //                 c += d[i];
    //                 d.erase(d.begin() + i);
    //             }
    //         }
    //         self(self, d, x ^ c);
    //     }
    // };

    // dfs(dfs, a, 0);

    vector<int> idxs(n);

    auto dfs = [&](auto self, int i, ll x) -> void {
        // cout << "i : " << i << " x : " << x << '\n';
        int out = n - __builtin_popcount(i);
        if(out == 0) {
            s.push_back(x);
            return;
        }
        for(int bm = 0; bm < (1 << (out - 1)); bm++) {
            int tbm = 1 + (bm << 1);
            int obm = 0;
            ll c = 0;
            int p = 0;
            for(int j = 0; j < n; j++) {
                if(((i >> j) & 1) == 0) {
                    idxs[p++] = j;
                }
            }
            for(int j = 0; j < out; j++) {
                if((tbm >> j) & 1) {
                    c += a[idxs[j]];
                    obm += 1 << idxs[j];
                }
            }
            // cout << "i : " << i << " obm : " << obm << '\n';
            // cout << "idxs : " << idxs << '\n';
            self(self, i + obm, c ^ x);
        }
    };

    dfs(dfs, 0, 0);

    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());

    cout << s.size() << '\n';

    // cout << "ct f : " << ct << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// //can't optimize this lol

// template<typename T>
// std::ostream& operator<<(std::ostream& os, set<T> s) {
//     for(auto &x: s) os << x << " ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;

//     vector<vector<ll>> poss(1 << n);
//     for(ll i = 0; i < 1 << n; i++) {
//         for(ll j = 0; j < 1 << n; j++) {
//             if((i & j) == j && __builtin_popcount(j) * 2 <= __builtin_popcount(i)) {
//                 ll k = i ^ j;
//                 for(ll x : poss[j]) {
//                     for(ll y : poss[k]) {
//                         poss[i].push_back(x^y);
//                     }
//                 }
//             }
//         }
//         ll c = 0;
//         for(ll j = 0; j < n; j++) {
//             if((i >> j) & 1) {
//                 c += a[j];
//             }
//         }
//         poss[i].push_back(c);
//         sort(poss[i].begin(), poss[i].end());
//         poss[i].erase(unique(poss[i].begin(), poss[i].end()), poss[i].end());
//     }

//     // for(ll i = 0; i < 1 << n; i++) {
//     //     cout << "i : " << i << " poss[i] : " << poss[i] << '\n';
//     // }

//     cout << poss[(1 << n) - 1].size() << '\n';

//     return 0;
// }

// // #include <bits/stdc++.h>
// // typedef long long ll;
// // typedef long double ld;
// // using namespace std;

// // template<typename T>
// // std::ostream& operator<<(std::ostream& os, const vector<T> v) {
// //     for(auto x : v) os << x << " ";
// //     return os;
// // }

// // signed main() {
// //     ios_base::sync_with_stdio(false);
// //     cin.tie(NULL);

// //     auto nck = [](ll n, ll k) {
// //         ll res = 1;
// //         for(ll i = 1; i <= n; i++) res *= n;
// //         for(ll i = 1; i <= k; i++) res /= i;
// //         for(ll i = 1; i <= n - k; i++) res /= i;
// //         return res;
// //     };

// //     vector f(13,vector<ll>(13));
// //     f[0][0] = 1;

// //     for(ll i = 1; i <= 12; i++) {
// //         for(ll j = 1; j <= i; j++) {
// //             for(ll k = 0; k <= i - j; k++) {
// //                 f[i][j] += f[i-j][k] * nck(i,j);
// //             }
// //         }
// //     }

// //     for(auto ff : f) cout << ff << '\n';

// //     return 0;
// // }

// // #include <bits/stdc++.h>
// // typedef long long ll;
// // typedef long double ld;
// // using namespace std;

// // template<typename T>
// // std::ostream& operator<<(std::ostream& os, const vector<T> v) {
// //     for(auto x : v) os << x << " ";
// //     return os;
// // }

// // signed main() {
// //     ios_base::sync_with_stdio(false);
// //     cin.tie(NULL);

// //     auto nck = [](ll n, ll k) {
// //         ll res = 1;
// //         for(ll i = 1; i <= n; i++) res *= n;
// //         for(ll i = 1; i <= k; i++) res /= i;
// //         for(ll i = 1; i <= n - k; i++) res /= i;
// //         return res;
// //     };

// //     vector f(13,vector<ll>(13));
// //     f[0][0] = 1;

// //     for(ll i = 1; i <= 12; i++) {
// //         for(ll j = 1; j <= i; j++) {
// //             for(ll k = 0; k <= i - j; k++) {
// //                 f[i][j] += f[i-j][k] * nck(i,j);
// //             }
// //         }
// //     }

// //     for(auto ff : f) cout << ff << '\n';

// //     return 0;
// // }