#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct Tree {
    static constexpr T base = INT_MAX;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
        Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cout << 200000 * log2l(200000) << '\n';

    int n, q; cin >> n >> q;
    map<int, set<int>> m;
    vector<int> a(n);
    Tree<int> tree(n);

    auto upd_val = [&](int idx, int x) -> void {
        //remove previous value
        int prev_x = a[idx];
        set<int> &s = m[prev_x];
        s.erase(idx);
        auto it = s.lower_bound(idx);
        if(it != s.begin()) {
            auto pit = prev(it);
            if(it != s.end()) {
                tree.update(*pit, idx);
            } else {
                tree.update(*pit, n);
            }
        }
        
        a[idx] = x;
        set<int> &s2 = m[x];
        s2.insert(idx);

        it = s2.upper_bound(idx);
        if(it != s2.end()) {
            tree.update(idx, *it);
        } else {
            tree.update(idx, n);
        }

        it = s2.lower_bound(idx);

        if(it != s2.begin()) {
            auto pit = prev(it);
            tree.update(*pit, idx);
        }
    };

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        upd_val(i, x);
    }

    for(int i = 0; i < q; i++) {
        int t; cin >> t;
        if(t == 1) {
            int k, u; cin >> k >> u;
            k--;
            upd_val(k, u);
        } else {
            int a, b; cin >> a >> b;
            a--;
            cout << (tree.query(a, b) < b ? "NO" : "YES" ) << "\n";
        }
    }



    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// struct MinTree {
//     static constexpr T base = INT_MAX;
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return min(a, b);
//     }
//     MinTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// template<typename T>
// struct MaxTree {
//     static constexpr T base = INT_MIN;
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return max(a, b);
//     }
//     MaxTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, q; cin >> n >> q;
//     MinTree<int> mint(n);
//     MaxTree<int> maxt(n);
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         mint.update(i, x);
//         maxt.update(i, x);
//     }

//     for(int i = 0; i < q; i++) {
//         int t; cin >> t;
//         if(t == 1) {
//             int k, u; cin >> k >> u;
//             k--;
//             mint.update(k, u);
//             maxt.update(k, u);
//         } else {
//             int a, b; cin >> a >> b;
//             a--;
//             cout << (mint.query(a,b) == maxt.query(a,b) ? "YES" : "NO") << '\n';
//         }
//     }

//     return 0;
// }
