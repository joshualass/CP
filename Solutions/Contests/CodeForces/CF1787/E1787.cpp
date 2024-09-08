#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
We should always try to make the most groups.
Let's do this greedily by making as many groups of size 2 as possible. If we can't make anymore groups of size 2, then we can't make anymore groups period.
*/

void solve() {
    int n, k, x; cin >> n >> k >> x;
    vector<int> unused(n + 1, 1);
    vector<vector<int>> groups(0);
    for(int i = 0; i <= n; i++) {
        if((i ^ x) <= n && unused[i] && unused[(i ^ x)]) {
            groups.push_back({});
            unused[i] = 0;
            unused[(i ^ x)] = 0;
            if(i) {
                groups.back().push_back(i);
            }
            if(i ^ x) {
                groups.back().push_back(i ^ x);
            }
            if(groups.size() == k) {
                break;
            }
        }
    }
    int remxor = 0;
    if(groups.size()) {
        for(int i = 0; i <= n; i++) {
            if(unused[i] && i) {
                groups.back().push_back(i);
                remxor ^= i;
            }
        }
    }
    if(groups.size() == k && remxor == 0) {
        cout << "YES\n";
        for(auto group : groups) {
            cout << group.size() << " ";
            for(int i = 0; i < group.size(); i++) {
                cout << group[i] << " \n"[i == group.size() - 1];
            }
        }
    } else {
        cout << "NO\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();
    
    // cerr << "OK" << endl;

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
//     for(auto x : adj) {
//         for(auto y : x) os << y << " ";
//         os << "\n";
//     }
//     return os;
// }

// void solve() {
//     int n, k, x; cin >> n >> k >> x;
//     bool ok = 1;
//     set<int> s;
//     for(int i = 0; i <= n; i++) s.insert(i);
//     vector<vector<int>> ss;
//     while(ss.size() != k) {
//         if(s.empty()) {
//             ok = 0;
//             break;
//         }
//         int hi = (*--s.end());
//         s.erase(hi);
//         int c = x ^ hi;
//         if(s.count(c)) {
//             if(c != 0) {
//                 ss.push_back({hi,c});
//             } else {
//                 ss.push_back({hi});
//             }
//             s.erase(c);
//         } else {
//             cout << "no workie hi : " << hi << '\n';
//             ok = 0;
//             break;
//         }
//     }
//     s.erase(0);
//     cout << "ss\n" << ss;
//     if(ok) {
//         for(int x : s) ss.back().push_back(x);
//         for(vector<int> v : ss) {
//             int a = 0;
//             for(int y : v) a ^= y;
//             if(a != x) ok = 0;
//         }
//         if(ok) {
//             cout << "YES\n";
//             for(vector<int> v : ss) {
//                 cout << v.size() << " ";
//                 sort(v.begin(), v.end());
//                 for(int i = 0; i < v.size(); i++) {
//                     cout << v[i] << " \n"[i == v.size() - 1];
//                 }
//             }
//             return;
//         }
//     }
//     cout << "NO\n";
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }