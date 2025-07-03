#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
make the following observations
1) if there are 0 inversions, not possible. 
2) first try entire subarray
3) second try removing elements from prefix / suffix only, this depends on one of the elements having a # of inversions that does not divide k
4) in the worst case where we can't do the above, we should consider the longest subarray that excludes endpoints that are not inverted

was able to generate a testcase that broke most my original ideas

1
6 2
3 1 2 5 6 4

thanks for reading
 -- ttfang
 
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
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

template<typename T>
struct MaxTree {
    static constexpr T base = -1;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
    }
    MaxTree(int n = 0, T def = base) {
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

template<typename T>
struct MinTree {
    static constexpr T base = 1e9;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    MinTree(int n = 0, T def = base) {
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

void solve() {
    
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }

    int res = 0;
    Tree<int> pre(n);
    MinTree<int> mintree(n);
    vector<int> il(n);

    for(int i = 0; i < n; i++) {
        il[i] = pre.query(a[i] + 1, n);
        pre.update(a[i], 1);    
        res = max(res, i - mintree.query(a[i] + 1, n) - 1);
        mintree.update(a[i], i);
    }

    Tree<int> suf(n);
    MaxTree<int> maxtree(n);
    vector<int> ir(n);

    for(int i = n - 1; i >= 0; i--) {
        ir[i] = suf.query(0, a[i]);
        suf.update(a[i], 1);
        res = max(res, maxtree.query(0, a[i]) - i - 1);
        maxtree.update(a[i], i);
    }

    ll inv = accumulate(il.begin(), il.end(), 0LL);

    // cout << "il : " << il << '\n';
    // cout << "ir : " << ir << '\n';

    if(inv == 0) {
        cout << "-1\n";
        return;
    }

    if(inv % k) {
        cout << n << '\n';
        return;
    }

    for(int i = n - 1; i >= 0; i--) {
        if(il[i] % k) {
            res = max(res, i);
            break;
        }
    }

    for(int i = 0; i < n; i++) {
        if(ir[i] % k) {
            res = max(res, n - i - 1);
        }
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

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     Tree(int n = 0, T def = base) {
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
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
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
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// int c = 0;

// ll get_inv(vector<int> p, int n) {
//     c++;
//     Tree<int> tree(n);
//     ll res = 0;
//     for(int i = 0; i < p.size(); i++) {
//         res += tree.query(p[i] + 1, n);
//         tree.update(p[i], 1);
//     }
//     // cout << "p : " << p << '\n';
//     // cout << "res : " << res << '\n';
//     return res;
// }

// void solve() {

//     int n, k; cin >> n >> k;
//     c = 0;

//     vector<int> a(n);
//     for(int &x : a) {
//         cin >> x;   
//         x--;
//     }

//     Tree<int> tree(n);

//     auto get_inv = [&](int l, int r) -> ll {
//         tree.v.assign(tree.size * 2, 0);
//         ll cnt = 0;
//         for(int i = l; i < r; i++) {
//             cnt += tree.query(a[i] + 1, n);
//             tree.update(a[i], 1);
//         }
//         return cnt;
//     };

//     if(get_inv(0, n) % k != 0) {
//         cout << n << '\n';
//         return;
//     }
    
//     int res = -1;
//     for(int r = 1; r <= n; r++) {
//         if(get_inv(0,r) % k != 0) res = r;
//     }
//     for(int l = 0; l < n; l++) if(get_inv(l, n) % k != 0) res = max(res, n - l);

//     while(a.size() && a.back() + 1 == a.size()) a.pop_back();
//     reverse(a.begin(), a.end());
//     int t = 0;
//     while(a.size() && a.back() == t++) a.pop_back();
//     reverse(a.begin(), a.end());

//     // for(int l = 0; l < n; l++) {
//     //     for(int r = l + 1; r <= n; r++) {
//     //         if(get_inv(l, r) % k != 0) res = max(res, r - l);
//     //     }
//     // }


//     for(int len = a.size(); len >= max(res, 1); len--) {
//         for(int l = 0; l + len <= a.size(); l++) {
//             if(get_inv(l, l + len) % k != 0) {
//                 cout << len << '\n';
//                 return;
//             }
//         }
//     }

//     cout << res << '\n';

//     // cout << res << '\n';




//     // cout << "-1\n";

//     // cout << "c : " << c << '\n';

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }