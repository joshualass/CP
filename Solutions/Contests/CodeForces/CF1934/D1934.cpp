// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void printans(ll n, vector<ll> ops) {
//     cout << ops.size() << '\n';
//     cout << n << " ";
//     for(int i = 0; i < ops.size(); i++) {
//         cout << ops[i] << " \n"[i == ops.size()-1];
//     }
// }

// void solve() {
//     ll n, m; cin >> n >> m;
//     if((n ^ m) < n) {
//         printans(n,{m});
//         return;
//     }
//     ll reduce = 0;
//     int onecnt = 0;
//     for(ll bit = 61; bit >= 0; bit--) {
//         if(n & (1LL << bit)) {
//             onecnt++;
//         }
//         if(onecnt == 2 && ((n & (1LL << bit))) || onecnt >= 2 && ((n & (1LL << bit)) == 0)) {
//             reduce |= (1LL << bit);
//         }
//     }
//     // cout << "reduce : " << reduce << '\n';
//     ll n2 = reduce ^ n;
//     if((n2 ^ m) < n) {
//         printans(n,{n2,m});
//         return;
//     }
//     cout << "-1\n";
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void solve() {
    ll n; cin >> n;
    if(__builtin_popcountll(n) & 1) {
        cout << "second" << endl;
    } else {
        cout << "first" << endl;
        ll p1 = 1;
        while(p1 * 2 <= n) {
            p1 <<= 1;
        }
        ll p2 = n ^ p1;
        cout << p1 << " " << p2 << endl;
    }
    ll a0, a1; cin >> a0 >> a1;
    while(a0 != 0) {
        if((__builtin_popcountll(a0) & 1) == 0) {
            ll p1 = 1;
            while(p1 * 2 <= a0) {
                p1 <<= 1;
            }
            ll p2 = a0 ^ p1;
            cout << p1 << " " << p2 << endl;
        } else if((__builtin_popcountll(a1) & 1) == 0) {
            ll p1 = 1;
            while(p1 * 2 <= a1) {
                p1 <<= 1;
            }
            ll p2 = a1 ^ p1;
            cout << p1 << " " << p2 << endl;
        }
        cin >> a0 >> a1;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // int N = 100;
    // vector<int> winning(N,0);
    // vector<vector<pair<int,int>>> losing_pairs(N);

    // for(int i = 1; i < winning.size(); i++) {
    //     for(int p1 = 1; p1 < i; p1++) {
    //         for(int p2 = 1; p2 < p1; p2++) {
    //             if((p1 ^ p2) == i && winning[p1] == 0 && winning[p2] == 0) {
    //                 winning[i] = 1;
    //                 losing_pairs[i].push_back({p1,p2});
    //             }
    //         }
    //     }
    // }

    // cout << "winning : " << winning << '\n';
    // for(int i = 0; i < N; i++) {
    //     cout << "i : " << i << " popcount : " << __builtin_popcount(i);
    //     for(pair<int,int> p : losing_pairs[i]) {
    //         cout << " " << p;
    //     }
    //     cout << '\n';
    // }
    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}