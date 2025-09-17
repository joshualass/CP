#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <forward_list>
#include <future>
#include <initializer_list>
#include <mutex>
#include <random>
#include <ratio>
#include <regex>
#include <scoped_allocator>
#include <system_error>
#include <thread>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Info {
    int lg, rg, all, res;
    Info(): lg(0), rg(0), all(0), res(0) {}
    // For a segment of length n that is "empty/off":
    // all = -n so lg/rg/res combine correctly.
    Info(int n): lg(0), rg(0), all(-n), res(0) {}
    Info(int lg, int rg, int all, int res): lg(lg), rg(rg), all(all), res(res) {}
};

inline Info operator+(const Info& lhs, const Info& rhs) {
    Info res;
    res.lg  = max(lhs.lg, lhs.all + rhs.lg);
    res.rg  = max(rhs.rg, rhs.all + lhs.rg);
    res.all = lhs.all + rhs.all;
    res.res = max({lhs.res, rhs.res, lhs.rg + rhs.lg});
    return res;
}

ostream& operator<<(ostream &os, const Info info) {
    os << "(" << info.lg << ", " << info.rg << ", " << info.all << ", " << info.res << ")";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    for (auto &x : v) os << x << " ";
    return os;
}

struct Node {
    Node* left;
    Node* right;
    Info info;
    Node(): left(nullptr), right(nullptr), info() {}
    explicit Node(const Info& info): left(nullptr), right(nullptr), info(info) {}
};

struct SparsestSegtree {
    int n;
    Node* root;

    explicit SparsestSegtree(int n_in) {
        // n = 1 is scary → same trick as your code
        int N = n_in + 1;
        n = N;
        // Single root node with "empty" segment info
        root = new Node(Info(n));
    }

    // Public update: set position idx to 'info'
    void update(int idx, const Info& val) {
        _update(root, 0, n, idx, val);
    }

    Info query() const {
        return root->info; // always valid
    }

private:
    // Recursively update; node 'cur' corresponds exactly to [l,r)
    void _update(Node*& cur, int l, int r, int idx, const Info& val) {
        if (idx < l || idx >= r) return; // no-op

        if (!cur) cur = new Node(Info(r - l)); // create on demand

        if (l + 1 == r) {
            // Leaf: overwrite with provided info
            cur->info = val;
            return;
        }

        int mid = (l + r) >> 1;

        // Recurse
        if (idx < mid) {
            _update(cur->left, l, mid, idx, val);
        } else {
            _update(cur->right, mid, r, idx, val);
        }

        // Combine children infos; if child missing, treat as empty segment
        const Info leftInfo  = cur->left  ? cur->left->info  : Info(mid - l);
        const Info rightInfo = cur->right ? cur->right->info : Info(r - mid);
        cur->info = leftInfo + rightInfo;
    }
};
void solve() {
    
    int n, q; cin >> n >> q;
    vector<int> a(n), b(n);
    // vector<SparsestSegtree> trees(n, SparsestSegtree(n));
    vector<SparsestSegtree> trees;
    for(int i = 0; i < n; i++) trees.push_back(SparsestSegtree(n));
    priority_queue<array<int,2>> pq;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        // cout << "i : " << i << " x :  " << x << '\n';
        a[i] = x;
        trees[x].update(i, Info(1, 1, 1, 1));
        int val = trees[x].query().res;
        b[x] = val;
        // cout << "i : " << i << " b[i] : " << b[i] << '\n';
        pq.push({val, x}); 
    }

    // cout << "b : " << b << '\n';

    for(int qq = 0; qq < q; qq++) {
        int i, x; cin >> i >> x;
        i--; x--;
        trees[a[i]].update(i, Info(0, 0, -1, 0));
        b[a[i]] = trees[a[i]].query().res;
        pq.push({b[a[i]], a[i]});
        a[i] = x;
        trees[x].update(i, Info(1, 1, 1, 1));
        int val = trees[x].query().res;
        b[x] = val;
        // cout << "i : " << i << " x : " << x << " val : " << val << '\n';
        pq.push({val, x});
        while(b[pq.top()[1]] != pq.top()[0]) {
            pq.pop();
        }
        cout << pq.top()[0] / 2 << " \n"[qq == q - 1];
        // cout << "pq.top x : " << pq.top()[1] << " val : " << pq.top()[0] << '\n';
        // cout << "qq : " << qq << " b : " << b << '\n';
    }

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

// /*
// try making O(n sqrt n) runtime with O(n) memory
// none of the homies like using n logn memory XXXX

// memory forces

// */

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// const int SQN = 550;

// struct Info {
//     int res, l, r, all;
//     Info(): res(0), l(0), r(0), all(0) {}
//     Info(int res, int l, int r, int all): res(res), l(l), r(r), all(all) {}
// };

// Info operator+(Info &lhs, Info &rhs) {
//     Info res;
//     res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
//     res.l = max(lhs.l, lhs.all + rhs.l);
//     res.r = max(rhs.r, rhs.all + lhs.r);
//     res.all = lhs.all + rhs.all;
//     return res;
// }

// void solve() {
    
//     int n, q; cin >> n >> q;

//     vector<vector<array<int,2>>> bidx(n); //[value], stores {present block id, idx in bvals}
//     vector<vector<int>> bvals;
//     vector<Info> infos;

//     set<array<int,2>> vals;

//     auto get_val = [&](int val) -> array<int,2> {
//         int p = 0;
//         Info res;
//         for(int i = 0; i < (n + SQN - 1) / SQN; i++) {
//             Info nx;
//             if(p < bidx[val].size() && i == bidx[val][p][0]) {
//                 nx = infos[bidx[val][p++][1]];
//             } else {
//                 nx = Info(0, 0, 0, -SQN);
//             }
//             res = res + nx;
//         }
//         array<int,2> rv = {res.res, val};
//         // cout << "rv : " << rv << '\n';
//         return rv;
//     };

//     auto update_info = [&](int bvidx, int block_id) -> void {
//         int res = 0, l = 0, r = 0;
//         for(int i = block_id * SQN, p = 0, cur = 0, curl; i < (block_id + 1) * SQN; i++) {
//             int in = 0;
//             if(p < bvals[bvidx].size() && i == bvals[bvidx][p]) {
//                 in = 1;
//                 p++;
//             }
//             if(in) {
//                 cur++;
//                 curl++;
//             } else {
//                 cur--;
//                 curl--;
//             }
//             cur = max(cur, 0);

//             res = max(res, cur);
//             l = max(res, curl);
//         }

//         for(int i = (block_id + 1) * SQN - 1, p = bvals[bvidx].size() - 1, cur = 0; i >= block_id * SQN; i--) {
//             int in = 0;
//             if(p >= 0 && i == bvals[bvidx][p]) {
//                 in = 1;
//                 p--;
//             }
//             if(in) {
//                 cur++;
//             } else {
//                 cur--;
//             }
//             r = max(r, cur);
//         }

//         int all = -SQN * bvals[bvidx].size() * 2;
//         infos[bvidx] = Info(res, l, r, all);
//     };

//     auto insert = [&](int idx, int val) -> void {
//         // cout << "insert called idx : " << idx << " val : " << val << '\n';
//         vals.erase(get_val(val));

//         int block_id = idx / SQN;

//         int i = 0;
//         while(i < bidx[val].size() && block_id > bidx[val][i][0]) i++;
//         if(!(i < bidx[val].size() && bidx[val][i][0] == block_id)) {
//             bidx[val].insert(bidx[val].begin() + i, {block_id, (int) bvals.size()});
//             bvals.push_back({});
//             infos.push_back(Info());
//         }

//         int bvidx = bidx[val][i][1];
        
//         i = 0;
//         while(i < bvals[bvidx].size() && idx > bvals[bvidx][i]) i++;
//         bvals[bvidx].insert(bvals[bvidx].begin() + i, idx);

//         update_info(bvidx, block_id);

//         vals.insert(get_val(val));
//     };

//     auto erase = [&](int idx, int val) -> void {
//         vals.erase(get_val(val));

//         int block_id = idx / SQN;

//         int i = 0;
//         while(i < bidx[val].size() && block_id > bidx[val][i][0]) i++;
//         int bvidx = bidx[val][i][1];
//         int p = 0;

//         if(bvidx >= bvals.size() || count(bvals[bvidx].begin(), bvals[bvidx].end(), idx) == 0) {
//             cout << "idx : " << idx << " val : " << val << '\n';

//             cout << "i : " << i << '\n';
//             cout << "bvidx : " << bvidx << '\n';
//             for(int i = 0; i < n; i++) {
//                 cout << "i : " << i << " bidx[i] : " << bidx[i] << '\n';
//             }
//             for(int i = 0; i < bvals.size(); i++) {
//                 cout << "i : " << i << " bvals[i] : " << bvals[i] << '\n';
//             }

//             assert(0);
//         }

//         while(bvals[bvidx][p] != idx) p++;
//         bvals[bvidx].erase(bvals[bvidx].begin() + p);

//         update_info(bvidx, block_id);

//         vals.insert(get_val(val));
//     };

//     vector<int> a(n);
//     for(int i = 0; i < n; i++) {
//         cin >> a[i];
//         a[i]--;
//         insert(i, a[i]);
//     }

//     vals.insert({0, -1});

//     for(int tr = 0; tr < q; tr++) {
//         int i, x; cin >> i >> x;
//         i--, x--;
//         erase(i, a[i]);
//         a[i] = x;
//         insert(i, x);
//         cout << (*--vals.end())[0] / 2 << " \n"[tr == q - 1];
//         // cout << (*--vals.end())[0] << " \n"[tr == q - 1];
//     }


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