#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k; cin >> n >> k;
    cout << "Second" << endl;
    vector<int> a(n, n - 1);
    while(accumulate(a.begin(), a.end(), 0)) {
        // cout << "a : " << a << endl;
        int i, j; cin >> i >> j;
        if(i == -1) return 0;
        if(i == 0) return 0;
        a[i-1] -= j;
        vector<int> b(n);
        iota(b.begin(), b.end(), 0);
        sort(b.begin(), b.end(), [&](const auto &lhs, const auto &rhs) -> bool {
            return a[lhs] > a[rhs];
        });
        vector<int> op;
        if(a[b[0]] == 1) {
            if(accumulate(a.begin(), a.end(), 0) <= k) {
                for(int i = 0; i < n; i++) {
                    if(a[i]) {
                        op.push_back(i);
                    }
                }
            } else {
                op.push_back(b[0]);
            }
        } else {
            for(int i = 0; i < j; i++) {
                if(a[b[i]] > 1) op.push_back(b[i]);
            }
        }

        cout << sz(op) << endl;
        for(int x : op) {
            cout << x + 1 << " ";
            a[x]--;
        }
        cout << endl;
    }

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// #define sz(x) (int) (x).size()

// template<typename T>
// ostream& operator<<(ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, k; cin >> n >> k;
//     vector<int> g(n);

//     for(int i = 1; i < n; i++) {
//         set<int> s;
//         for(int j = 1; j <= min(k, i); j++) {
//             s.insert(g[i - j]);
//         }
//         for(int j = 0; j <= n; j++) {
//             if(s.count(j) == 0) {
//                 g[i] = j;
//                 break;
//             }
//         }
//     }

//     cout << g << endl;

//     vector<int> a(n, n - 1);
//     vector<vector<int>> poss(n, vector<int>(k * 2 + 1));
    
//     auto get = [&]() -> int {
//         int res = 0;
//         for(int x : a) res ^= g[x];
//         return res;
//     };

//     int turn;
//     if(get()) {
//         cout << "First" << endl;
//         turn = 0;
//     } else {
//         cout << "Second" << endl;
//         turn = 1;
//     }

//     auto take = [&](int i, int x) -> void {
//         // assert(0 <= i && i < n);
//         // assert(1 <= x && x <= k);
//         // assert(x <= a[i]);
//         a[i] -= x;
//         poss[i].assign(k * 2 + 1, 0);
//         for(int j = 1; j <= min(a[i], k); j++) {
//             int impact = g[a[i]] ^ a[a[i] - j];
//             poss[i][impact] = 1;
//         }
//     };

//     while(accumulate(a.begin(), a.end(), 0)) {
//         if(turn == 0) {
//             array<int,2> op = {-1, -1}; // {idx, amount}
//             int cur = get();
//             for(int i = 0; i < n; i++) {
//                 if(poss[i][cur]) {
//                     for(int j = 1; j <= min(a[i], k); j++) {
//                         int impact = g[a[i]] ^ a[a[i] - j];
//                         if(impact == cur) {
//                             op = {i, j};
//                             break;
//                         }
//                     }
//                     break;
//                 }
//             }

//             // assert(op != array<int,2>{-1,-1});
//             cout << op[0] + 1 << " " << op[1] << endl;
//         } else {
//             int k; cin >> k;
//             if(k == -1) {
//                 return 0;
//             }
//             if(k == 0) {
//                 return 0;
//             }

//         }
//     }

//     return 0;
// }
