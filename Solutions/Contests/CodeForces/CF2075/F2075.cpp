#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    int n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        return val1 + val2;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node];
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(int l, int r, D val) { //[l,r)
        _update(1,0,size,l,r, val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            int mid = (currl + currr) / 2;
            return query_comb(
                _query(node * 2, currl, mid, targetl, targetr),
                _query(node * 2 + 1, mid, currr, targetl, targetr)
            );
        }
    }
};

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    set<int> s(a.begin(), a.end());
    int p = 0;
    map<int,int> m;
    for(int x : s) m[x] = p++;
    for(int &x : a) x = m[x];

    vector<vector<int>> b(p);
    for(int i = 0; i < n; i++) {
        b[a[i]].push_back(i);
    }

    vector<array<int,2>> l, r;
    int c = p;
    for(int i = 0; i < n; i++) {
        if(a[i] < c) {
            l.push_back({i, a[i]});
            c = a[i];
        }
    }

    c = -1;
    for(int i = n - 1; i >= 0; i--) {
        if(a[i] > c) {
            r.push_back({i, a[i]});
            c = a[i];
        }
    }

    reverse(r.begin(), r.end());

    

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

// template<typename T, typename D>
// struct Lazy {
//     static constexpr T qn = 0; // query neutral, when we query, doing the operation with this value won't change our query
//     static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
//     vector<T> v;      //stores values at each index we are querying for
//     vector<D> lazy;   //stores lazy update values
//     int n, size;
//     //if OJ is not up to date, remove all occurrences of ln
//     Lazy(int n = 0, T def = qn) {
//         this->n = n;
//         this->size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//         lazy.assign(size * 2, ln);
//     }
//     bool isLeaf(int node) {return node >= size;}
//     T query_comb(T val1, T val2) {//update this depending on query type
//         return max(val1, val2);
//     }
//     //how we combine lazy updates to lazy
//     void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
//         lazy[node] += val;
//     }
//     void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
//         v[node] += lazy[node];
//     }
//     void push_lazy(int node, int size) {
//         main_comb(node, size); //push lazy change to current node
//         if(!isLeaf(node)) {
//             lazy_comb(node * 2, lazy[node]);
//             lazy_comb(node * 2 + 1, lazy[node]);
//         }
//         lazy[node] = ln;
//     }
//     void update(int l, int r, D val) { //[l,r)
//         _update(1,0,size,l,r, val);
//     }
//     void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
//         if (currl >= targetr || currr <= targetl) return;
//         push_lazy(node, currr - currl);
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
//         } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
//             int mid = (currl + currr) / 2;
//             _update(node * 2, currl, mid, targetl, targetr, val);
//             _update(node * 2 + 1, mid, currr, targetl, targetr, val);
//             push_lazy(node * 2, (currr - currl) / 2);
//             push_lazy(node * 2 + 1, (currr - currl) / 2);
//             v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
//         }
//     }
//     T query(int l, int r) { // [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
//         if(currr <= targetl || currl >= targetr) return qn; 
//         push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             return v[node];
//         } else {
//             int mid = (currl + currr) / 2;
//             return query_comb(
//                 _query(node * 2, currl, mid, targetl, targetr),
//                 _query(node * 2 + 1, mid, currr, targetl, targetr)
//             );
//         }
//     }
// };

// void solve() {
//     int n; cin >> n;
//     vector<int> a(n);
//     for(int &x : a) cin >> x;
//     set<int> cs(a.begin(), a.end());
//     map<int,int> m;
//     int p = 0;
//     for(int x : cs) {
//         m[x] = p++;
//     }
//     for(int &x : a) x = m[x];
    
//     Tree<int> tree(p);
//     Lazy<int,int> lazy(p);

//     for(int i = 0; i < n; i++) {
//         int x = a[i];
//         tree.update(x, tree.at(x) + 1);
//         lazy.update(x, x + 1, tree.query(0, x) - lazy.query(x, x + 1));
//     }

//     int res = 0;
//     for(int i = 0; i < n; i++) {
//         int x = a[i];
//         lazy.update(x + 1, p, -1);
//         int q = lazy.query(x+1, p);
//         cout << "i : " << i << " q : " << q << '\n';
//         res = max(res, q);
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