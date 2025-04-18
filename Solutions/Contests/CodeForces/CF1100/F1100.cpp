#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
can use the fact that dim of any basis is less than 20, so we only add at most 20 vectors to each of the bases. 
handle things offline. Originally O(q logn d^2), now O(n d^2 + q d) :)
did not need to binary search this. 
*/

const int d = 20;
struct B {

    array<int,d> basis = {};
    B(): basis({}) {}

    B& operator=(const B& other) {
        this->basis = other.basis;
        return *this;
    }

    B operator+(const B& other) const {
        B res;
        res.basis = this->basis;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(other.basis[bit]) res.insert(other.basis[bit]);
        }
        return res;
    }

    bool insert(int x) { //return 0/1 if the insert failed. 
        // cout << "insert x : " << x << '\n';
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    basis[bit] = x;
                    return 1;
                }
            }
        }
        return 0;
    }

    bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
        for(int bit = d - 1; bit >= 0; bit--) {
            if((x >> bit) & 1) {
                if(basis[bit]) {
                    x ^= basis[bit];
                } else {
                    return 0;
                }
            }
        }
        return 1;
    }

    int query() {
        int res = 0;
        for(int bit = d - 1; bit >= 0; bit--) {
            if(((res >> bit) & 1) == 0) res ^= basis[bit];
        }
        return res;
    }
};

// const int d = 60;
// struct B {

//     array<ll,d> basis = {};
//     B(): basis({}) {}

//     B& operator=(const B& other) {
//         this->basis = other.basis;
//         return *this;
//     }

//     B operator+(const B& other) const {
//         B res;
//         res.basis = this->basis;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(other.basis[bit]) res.insert(other.basis[bit]);
//         }
//         return res;
//     }

//     bool insert(ll x) { //return 0/1 if the insert failed. 
//         // cout << "insert x : " << x << '\n';
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     basis[bit] = x;
//                     return 1;
//                 }
//             }
//         }
//         return 0;
//     }

//     bool find(ll x) { //return 0/1 if element is in the basis, does not insert. 
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     return 0;
//                 }
//             }
//         }
//         return 1;
//     }

//     ll query() {
//         ll res = 0;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(((res >> bit) & 1) == 0) res ^= basis[bit];
//         }
//         return res;
//     }
// };

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    vector<B> bases(n);
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int q; cin >> q;
    vector<vector<array<int,2>>> queries(n);

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[r - 1].push_back({l - 1, i});
    }

    vector<int> res(q);

    for(int i = 0; i < n; i++) {

        int l = 0, r = i;
        while(l != r) {
            int m = (l + r) / 2;
            if(bases[m].find(a[i])) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        for(int j = l; j <= i; j++) bases[j].insert(a[i]);
        for(auto [l, id] : queries[i]) {
            res[id] = bases[l].query();
        }

    }

    for(int x : res) cout << x << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// struct sparse {
//     vector<vector<T>> sparsetable;
//     int n, d;
//     sparse() {}
//     sparse(vector<T> a) {
//         buildTable(a);
//     }
//     T op(T a, T b) {
//         return a + b;
//     }
//     void buildTable(vector<T> a) {
//         n = a.size();
//         d = 32 - __builtin_clz(n);
//         sparsetable.assign(n, vector<T>(d));
//         for(int depth = 0; depth < d; depth++) {
//             for(int i = 0; i < n; i++) {
//                 if(depth) {
//                     sparsetable[i][depth] = op(sparsetable[i][depth - 1], sparsetable[min(n - 1, i + (1 << (depth - 1)))][depth - 1]);
//                 } else {
//                     sparsetable[i][depth] = a[i];
//                 }
//             }
//         }
//     }
//     //[l,r) always. 
//     T query(int l, int r) {
//         int depth = 31 - __builtin_clz(r - l);
//         return op(sparsetable[l][depth], sparsetable[max(l,r - (1 << depth))][depth]);
//     }
// };

// const int d = 20;
// struct B {

//     array<int,d> basis = {};
//     B(): basis({}) {}

//     B& operator=(const B& other) {
//         this->basis = other.basis;
//         return *this;
//     }

//     B operator+(const B& other) const {
//         B res;
//         res.basis = this->basis;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(other.basis[bit]) res.insert(other.basis[bit]);
//         }
//         return res;
//     }

//     bool insert(int x) { //return 0/1 if the insert failed. 
//         // cout << "insert x : " << x << '\n';
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     basis[bit] = x;
//                     return 1;
//                 }
//             }
//         }
//         return 0;
//     }

//     bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     return 0;
//                 }
//             }
//         }
//         return 1;
//     }

//     int query() {
//         int res = 0;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(((res >> bit) & 1) == 0) res ^= basis[bit];
//         }
//         return res;
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<B> a(n);
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         a[i].insert(x);
//     }

//     sparse<B> s(a);

//     int q; cin >> q;
//     for(int i = 0; i < q; i++) {
//         int l, r; cin >> l >> r;
//         l--;
//         cout << s.query(l, r).query() << '\n';
//     }

//     return 0;
// }


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// //todo optimize by using sqrt decomp

// const int SN = 710;

// const int d = 30;
// struct B {

//     array<int,d> basis = {};
//     B(): basis({}) {}

//     B& operator=(const B& other) {
//         this->basis = other.basis;
//         return *this;
//     }

//     B operator+(const B& other) const {
//         B res;
//         res.basis = this->basis;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(other.basis[bit]) res.insert(other.basis[bit]);
//         }
//         return res;
//     }

//     bool insert(int x) { //return 0/1 if the insert failed. 
//         // cout << "insert x : " << x << '\n';
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     basis[bit] = x;
//                     return 1;
//                 }
//             }
//         }
//         return 0;
//     }

//     bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     return 0;
//                 }
//             }
//         }
//         return 1;
//     }

//     int query() {
//         int res = 0;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(((res >> bit) & 1) == 0) res ^= basis[bit];
//         }
//         return res;
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;

//     int nb = (n + SN - 1) / SN;
//     vector<vector<B>> pre(nb, vector<B>(SN)), suf(nb, vector<B>(SN));

//     for(int i = 0; i < nb; i++) {
//         B pb;
//         for(int j = 0; i * nb + j < n; j++) {
//             pb.insert(a[i * nb + j]);
//             pre[i][j] = pb;
//         }
//         B sb;
//         for(int j = min(n - 1 - i * nb, SN - 1); j >= 0; j--) {
//             sb.insert(a[i * nb + j]);
//             suf[i][j] = sb;
//         }
//     }

//     vector<vector<B>> b(nb, vector<B>(nb));

//     for(int i = 0; i < nb; i++) {
//         for(int j = i; j < nb; j++) {
//             if(i == j) {
//                 b[i][j] = suf[i][0];
//             } else {
//                 b[i][j] = b[i][j-1] + suf[j][0];
//             }
//         }
//     }

//     int q; cin >> q;
//     for(int i = 0; i < q; i++) {
//         int l, r; cin >> l >> r;
//         l--;

//     }

//     return 0;
// }


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// const int d = 20;
// struct B {

//     array<int,d> basis = {};
//     B(): basis({}) {}

//     B& operator=(const B& other) {
//         this->basis = other.basis;
//         return *this;
//     }

//     B operator+(const B& other) const {
//         B res;
//         res.basis = this->basis;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(other.basis[bit]) res.insert(other.basis[bit]);
//         }
//         return res;
//     }

//     bool insert(int x) { //return 0/1 if the insert failed. 
//         // cout << "insert x : " << x << '\n';
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     basis[bit] = x;
//                     return 1;
//                 }
//             }
//         }
//         return 0;
//     }

//     bool find(int x) { //return 0/1 if element is in the basis, does not insert. 
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if((x >> bit) & 1) {
//                 if(basis[bit]) {
//                     x ^= basis[bit];
//                 } else {
//                     return 0;
//                 }
//             }
//         }
//         return 1;
//     }

//     int query() {
//         int res = 0;
//         for(int bit = d - 1; bit >= 0; bit--) {
//             if(((res >> bit) & 1) == 0) res ^= basis[bit];
//         }
//         return res;
//     }
// };

// B base;

// template<typename T>
// struct Tree {
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     Tree(int n = 0) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, base);
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

//     int n; cin >> n;

//     Tree<B> tree(n);
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         B b;
//         b.insert(x);
//         tree.update(i, b);  
//     }

//     int q; cin >> q;
//     for(int i = 0; i < q; i++) {
//         int l, r; cin >> l >> r;
//         cout << (tree.query(l - 1, r)).query() << '\n';
//     }


//     return 0;
// }
