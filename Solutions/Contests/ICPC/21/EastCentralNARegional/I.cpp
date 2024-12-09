#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int sp, su; cin >> sp >> su;
    int n = sp + su;
    int np = sp, nu = su;
    vector<int> a(n);
    vector<int> ia(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        ia[x] = i;
    }
    int ep, eu; cin >> ep >> eu;
    vector<int> b(n), ib(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        b[i] = x;
        ib[x] = i;
    }

    int res = 0;
    int musttoggle = 0;
    for(int i = 0; i < ep; i++) {
        int val = b[i];
        int start_idx = ia[val];
        if(start_idx >= sp) {
            // cout << "norm toggle i ep : " << i << '\n';
            res++;
        } else {
            for(int j = start_idx + 1; j < n; j++) {
                if(ib[a[j]] < i) {
                    musttoggle = 1;
                }
            }
            if(musttoggle) {
                // cout << "i ep : " << i << '\n';
                res += 2;
            }
        }
    }
    musttoggle = 0;
    for(int i = 0; i < eu; i++) {
        int val = b[n-i-1];
        int start_idx = ia[val];
        if(start_idx < sp) {
            // cout << "norm toggle i eu : " << i << '\n';
            res++;
        } else {
            for(int j = start_idx - 1; j >= 0; j--) {
                if(ib[a[j]] > n-i-1) {
                    musttoggle = 1;
                }
            }
            if(musttoggle) {
                // cout << "i eu : " << i << '\n';
                res += 2;
            }
        }
    }

    cout << res << '\n';

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, set<T> s) {
//     for(auto &x: s) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     // string s; cin >> s;
//     // int lo, hi; cin >> lo >> hi;

//     // for(int tt = lo; tt <= hi; tt++) {
//         // string bin = s + to_string(tt) + ".in";
//         // string bans = s + to_string(tt) + ".ans";
//         // freopen(bin.c_str(),"r",stdin);

//         int sp, su; cin >> sp >> su;
//         int n = sp + su;
//         int np = sp, nu = su;
//         vector<int> a(n);
//         vector<int> ia(n);
//         for(int i = 0; i < n; i++) {
//             int x; cin >> x;
//             x--;
//             a[i] = x;
//             ia[x] = i;
//         }
//         int ep, eu; cin >> ep >> eu;
//         vector<int> b(n), ib(n);
//         for(int i = 0; i < n; i++) {
//             int x; cin >> x;
//             x--;
//             b[i] = x;
//             ib[x] = i;
//         }

//         int res = 0;
//         set<int> to_toggle;
//         int res2 = 0;

//         for(int i = 0; i < n; i++) {
//             int start_idx = ia[i];
//             int startpin = start_idx < sp;

//             int end_idx = ib[i];
//             int endpin = end_idx < ep;

//             if(startpin != endpin) {
//                 res++;
//             } else {
//                 int add2 = 0;
//                 if(startpin) {
//                     for(int j = end_idx - 1; j >= 0; j--) {
//                         if(ia[b[j]] > start_idx) {
//                             add2 = 2;
//                         }
//                     }
//                     if(add2) {
//                         np--;
//                         nu++;
//                     }
//                 } else {
//                     for(int j = end_idx + 1; j < n; j++) {
//                         if(ia[b[j]] < start_idx) {
//                             add2 = 2;
//                         }
//                     }
//                     if(add2) {
//                         np++;
//                         nu--;
//                     }
//                 }
//                 if(add2) {
//                     to_toggle.insert(i);
//                     res2++;
//                 }
//                 res += add2;
//             }
//         }


//         cout << res << '\n';

//         // freopen(bans.c_str(),"r",stdin);
//         // int cc; cin >> cc;

//         // cout << "bin : " << bin << " test case : " << tt << " correct : " << cc << " ours : " << res << '\n';

//     // }


//     cout << "to_toggle : " << to_toggle << '\n';

//     vector<int> new_arr(n);
//     int pp = 0, up = n - 1;
//     for(int i = 0; i < sp; i++) {
//         if(to_toggle.count(a[i]) == 0) {
//             new_arr[pp++] = a[i];
//         }
//     }

//     for(int i = 0; i < su; i++) {
//         if(to_toggle.count(a[n-i-1]) == 0) {
//             new_arr[up--] = a[n-i-1];
//         }
//     }

//     for(int i = 0; i < sp; i++) {
//         if(to_toggle.count(a[i]) == 1) {
//             new_arr[up--] = a[i];
//         }
//     }

//     for(int i = 0; i < su; i++) {
//         if(to_toggle.count(a[n-i-1]) == 1) {
//             new_arr[pp++] = a[n-i-1];
//         }
//     }
//     cout << "np : " << np << " nu : " << nu << '\n';
//     cout << "new_arr : " << new_arr << '\n';

//     return 0;
// }