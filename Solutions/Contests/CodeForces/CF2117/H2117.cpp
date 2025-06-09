#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve() {
    
    

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

// int l[300000 * 18], r[300000 * 18], p[300000 * 18];
// int info[300000 * 18][4];
// int a[300000];


// void solve() {
    
    

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// /*
// have some data structure that can support the following operation
// for a given index i, find the largest k-majority possible that includes this element 
// */

// struct Info {
//     int res, l, r, all;
//     Info(): res(0), l(0), r(0), all(0) {}
//     Info(int res, int l, int r, int all): res(res), l(l), r(r), all(all) {}
// };

// Info operator+(Info lhs, Info rhs) {
//     Info res;
//     res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
//     res.l = max(lhs.l, lhs.all + rhs.l);
//     res.r = max(rhs.r, rhs.all + lhs.r);
//     res.all = lhs.all + rhs.all;
//     return res;
// }

// Info base;
// struct Tree {
//     typedef Info T;
//     vector<unordered_map<int, Info>> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     T get(int x, int cur) {
//         if(v[cur].count(x)) {
//             return v[cur][x];
//         }
//         int depth = 31 - __builtin_clz(cur);
//         int sz = size >> depth;
//         return Info(0, 0, 0, -sz);
//     }
//     void upd(int x, int cur, T info) {
//         int depth = 31 - __builtin_clz(cur);
//         int sz = size >> depth;
//         if(info.l == 0 && info.r == 0 && info.res == 0 && info.all == -sz) {
//             v[cur].erase(x);
//         } else {
//             v[cur][x] = info;
//         }
//     }
//     Tree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.resize(size * 2);
//     }
//     void update(int pos, int x, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         upd(x, curr, val);
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 upd(x, curr / 2, f(get(x, curr ^ 1), get(x, curr)));
//             } else {
//                 upd(x, curr / 2, f(get(x, curr), get(x, curr ^ 1)));
//             }
//             curr /= 2;
//         }
//     }
//     T query(int x) {
//         return get(x, 1);
//     }
// };

// void solve() {
    
//     int n, q; cin >> n >> q;
//     vector<int> a(n);
//     Tree tree(n);

//     priority_queue<array<int,2>> pq;

//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         a[i] = x;
//         tree.update(i, x, Info(1, 1, 1, 1));
//         pq.push({tree.query(x).res, x});
//     }

//     for(int i = 0; i < q; i++) {
//         int idx, x; cin >> idx >> x;
//         idx--;
        
//         tree.update(idx, a[idx], Info(0, 0, 0, -1));
//         pq.push({tree.query(a[idx]).res, a[idx]});

//         a[idx] = x;
//         tree.update(idx, x, Info(1,1,1,1));
//         pq.push({tree.query(x).res, x});

//         while(1) {
//             auto [val, x] = pq.top();
//             if(val == tree.query(x).res) break;
//             pq.pop();
//         }
//         cout << pq.top()[0] / 2 << " \n"[i == q - 1];
//     }

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }