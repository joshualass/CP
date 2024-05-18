// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// ll dist[10000];
// const ll maxd = 13; 
// ll powpow[maxd+1];

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// void solve() {
//     ll n, m, k; cin >> n >> m >> k;
//     vector<string> a(n);
//     for(auto &x : a) cin >> x;
//     ll res = 0;
//     for(ll i = 0; i < k; i++) {
//         ll x, y, p; cin >> x >> y >> p;
//         x--; y--;
//         vector<ll> v;
//         for(ll j = max(0LL, x - maxd); j <= min(n - 1, x + maxd); j++) {
//             for(ll k = max(0LL, y - maxd); k <= min(m - 1, y + maxd); k++) {
//                 if(a[j][k] == '#') {
//                     v.push_back(dist[(x-j) * (x-j) + (y-k) * (y-k)]);
//                     cout << "huh : " << (x-j) * (x-j) + (y-k) * (y-k) << " " << dist[(x-j) * (x-j) + (y-k) * (y-k)] << '\n';
//                 }
//             }
//         }
//         sort(v.begin(), v.end());
//         ll lo = 0;
//         ll best = 0;
//         for(ll i = 1; i <= maxd; i++) {
//             while(lo != v.size() && v[lo] <= i) lo++;
//             best = max(best, lo * p - powpow[i]);
//         }
//         cout << "i : " << i << " best : " << best << '\n';
//         cout << "v ? " << v << '\n';
//         res += best;
//     }
//     cout << res << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
//     powpow[0] = 0;
//     powpow[1] = 3;
//     for(ll i = 2; i <= maxd; i++) {
//         powpow[i] = powpow[i-1] * 3;
//     }
//     for(ll i = 0; i < 10000; i++) {
//         ll j = 0;
//         while(j * j < i) j++;
//         dist[i] = j;
//     }
//     ll casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

const int maxd = 13;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x : a) cin >> x;

    vector<int> dp(1 << maxd);
    map<pair<int,int>,int> t;
    for(int i = 0; i < k; i++) {
        int x, y, p; cin >> x >> y >> p;
        x--; y--;
        t[{x,y}] = p;
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(t.count({i,j})) {
                vector<int> cnts(maxd);
                for(int k = 0; k < n; k++) {
                    for(int l = 0; l < m; l++) {
                        for(int d = 0; d < maxd; d++) {
                            if(a[k][l] == '#' && (i - k) * (i - k) + (j - l) * (j - l) <= (d + 1) * (d + 1)) {
                                cnts[d]++;
                            }
                        }
                    }
                }
                for(int k = 0; k < maxd; k++) {
                    cnts[k] *= t[{i,j}];   
                }
                for(int bm = (1 << maxd) - 1; bm >= 0; bm--) {
                    for(int k = 0; k < maxd; k++) {
                        if(bm & (1 << k)) {
                            dp[bm] = max(dp[bm], dp[bm ^ (1 << k)] + cnts[k]);
                        }
                    }
                }
            }
        }
    }
    int res = 0;
    for(int bm = 0; bm < 1 << maxd; bm++) {
        int p = 1;
        int c = dp[bm];
        for(int i = 0; i < maxd; i++) {
            p *= 3;
            if(bm & (1 << i)) {
                c -= p;
            }
        }
        res = max(res, c);
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