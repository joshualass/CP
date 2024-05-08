#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

//not good at maths >.<

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

void solve() {
    ll n, m; cin >> n >> m;
    ll res = 0;

    for(ll p = 1; p * p <= n; p++) {
        for(ll q = 1; q * q <= m; q++) {
            if(gcd(p,q) == 1) {
                ll base = 1;
                while(p * base * (p + q) <= n && q * base * (p + q) <= m) {
                    
                    res++;
                    base++;
                }
            }
        }
    }
    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // vector<pair<int,int>> a;
    // for(int i = 1; i <= 100; i++) {
    //     for(int j = 1; j <= 100; j++) {
    //         if(i * gcd(i,j) % (i + j) == 0) {
    //             // cout << "{" << i << ", " << j << "}";
    //             a.push_back({i,j});
    //         }
    //     }
    //     // cout << '\n';
    // }

    // sort(a.begin(), a.end(), [](auto &lhs, auto &rhs) -> bool {
        // if(lhs.first + lhs.second == rhs.first + rhs.second) {
        //     return lhs < rhs;
    //     // } else {
    //     //     return lhs.first + lhs.second < rhs.first + rhs.second;
    //     // }
    //     // return lhs < rhs;
    //     if(gcd(lhs.first,lhs.second) == gcd(rhs.first,rhs.second)) {
    //         return lhs < rhs;
    //     } else {
    //         return gcd(lhs.first,lhs.second) < gcd(rhs.first,rhs.second);
    //     }
    // });

    // for(auto x : a) cout << x << " g : " << gcd(x.first, x.second) << '\n';

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve() {
//     ll n, m; cin >> n >> m;
//     ll res = n;
//     for(ll b = 2; b <= m; b++) {
//         res += (n + b) / (b * b);
//     }
//     cout << res << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }