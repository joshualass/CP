//https://www.spoj.com/problems/HORRIBLE/
//tested andrew's lazy segment tree and going to optimize it a bit
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// #include <bits/stdc++.h>
// typedef long long ll;
// using namespace std;

// /*
// famous words from master Andwerp
// lets say that we have a range that is k values in length
// the range sum, however we defined sum, is initially equal to src
// fmodifyk just returns the new sum, after adding, however we defined add, val to all k elements in the range
// in the examples, return src + val is fine for querying the min or max because min and max don't care about how many elements are changed
// but querying the sum on the range does care.
// also, if we were to define sum as the xor sum, then fmodifyk would be return src ^ (val * (k % 2))
// */

// template <typename T>
// struct SegtreeLazy {
//     public:
//         T n;
//         T* t;    //stores product of range
//         T* d;    //lazy tree
//         T uneut, qneut;

//         //single element modify
//         function<T(T, T)> modifyElement;

//         //k element modify
//         function<T(T, T, T)> modifyRange;

//         //product of two elements for query
//         function<T(T, T)> queryType;

//         SegtreeLazy(int maxSize, T updateNeutral, T queryNeutral, function<T(T, T)> modifyElement, function<T(T, T, T)> modifyRange, function<T(T, T)> queryType) {
//             n = maxSize;
//             uneut = updateNeutral;
//             qneut = queryNeutral;

//             this -> modifyElement = modifyElement;
//             this -> modifyRange = modifyRange;
//             this -> queryType = queryType;

//             //raise n to nearest pow 2
//             int x = 1;
//             while(x < n) {
//                 x <<= 1;
//             }
//             n = x;

//             t = new T[n * 2];
//             d = new T[n * 2];

//             //make sure to initialize values
//             for(T i = 0; i < n * 2; i++){
//                 t[i] = uneut;
//             }
//             for(T i = 0; i < n * 2; i++){
//                 d[i] = uneut;
//             }
//         }

//         void modify(int l, int r, T val) {    //modifies the range [l, r)
//             _modify(l, r, val, 0, n, 1);
//         }

//         void modify(int ind, T val) { //modifies the range [ind, ind + 1)
//             _modify(ind, ind + 1, val, 0, n, 1);
//         }

//         T query(int l, int r) {   //queries the range [l, r)
//             return _query(l, r, 0, n, 1);
//         }

//         T query(int ind) {    //queries the range [ind, ind + 1)
//             return _query(ind, ind + 1, 0, n, 1);
//         }

//     private:
//         //calculates value of node based off of children
//         //k is the amount of values that this node represents. 
//         void combine(int ind, T k) {
//             if(ind >= n){
//                 return;
//             }
//             int l = ind * 2;
//             int r = ind * 2 + 1;
//             //make sure children are correct value before calculating
//             push(l, k / 2);
//             push(r, k / 2);
//             t[ind] = queryType(t[l], t[r]);
//         }

//         //registers a lazy change llo this node
//         void apply(int ind, T val) {
//             d[ind] = modifyElement(d[ind], val);
//         }

//         //applies lazy change to this node
//         //k is the amount of values that this node represents. 
//         void push(int ind, T k) {
//             if(d[ind] == uneut) {
//                 return;
//             }
//             t[ind] = modifyRange(t[ind], d[ind], k);
//             if(ind < n) {
//                 int l = ind * 2;
//                 int r = ind * 2 + 1;
//                 apply(l, d[ind]);
//                 apply(r, d[ind]);
//             }
//             d[ind] = uneut;
//         }

//         void _modify(int l, int r, T val, int tl, int tr, int ind) {
//             if(l == r){
//                 return;
//             }
//             if(d[ind] != uneut) {
//                 push(ind, tr - tl);
//             }
//             if(l == tl && r == tr) {
//                 apply(ind, val);
//                 push(ind, tr - tl);
//                 return;
//             }
//             int mid = tl + (tr - tl) / 2;
//             if(l < mid) {
//                 _modify(l, min(r, mid), val, tl, mid, ind * 2);
//             }
//             if(r > mid) {
//                 _modify(max(l, mid), r, val, mid, tr, ind * 2 + 1);
//             }
//             combine(ind, tr - tl);
//         }

//         T _query(int l, int r, int tl, int tr, T ind) {
//             if(l == r){
//                 return qneut;
//             }  
//             if(d[ind] != uneut) {
//                 push(ind, tr - tl);
//             }
//             if(l == tl && r == tr){
//                 return t[ind];
//             }
//             int mid = tl + (tr - tl) / 2;
//             T lans = qneut;
//             T rans = qneut;
//             if(l < mid) {
//                 lans = _query(l, min(r, mid), tl, mid, ind * 2);
//             }
//             if(r > mid) {
//                 rans = _query(max(l, mid), r, mid, tr, ind * 2 + 1);
//             }
//             return queryType(lans, rans);
//         }
// };

template<typename T>
struct Lazy {
    static constexpr T ln = 0, qn = 0; //stores the starting values at all nodes, 
    vector<T> v;      //stores values at each index we are querying for
    vector<T> lazy;   //stores lazy updates at each node
    vector<bool> upd; //stores at each node, whether there is a lazy update to push
    int n, size;

    Lazy(int n) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, 0);
        lazy.assign(size * 2, 0);
        upd.assign(size * 2, 0);
    }
    bool isLeaf(int node) {
        return node >= size;
    }
    T query_comb(T val1, T val2) {//update this depending on query type
        return val1 + val2;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, T val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] = lazy[node] + val; 
        upd[node] = 1;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] += lazy[node] * size;
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
            upd[node * 2] = 1;
            upd[node * 2 + 1] = 1;
        }
        lazy[node] = ln;
        upd[node] = 0;
    }
    void update(int l, int r, T val) {
        _update(1,0,size,l,r,val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, T &val) {
        if(upd[node]) {
            push_lazy(node,currr-currl);
        }
        if (currl >= targetr || currr <= targetl) { //there is no overlap
            return; //do nothing if there is no overlap
        }
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
            push_lazy(node, currr-currl);
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(int l, int r) {
        return _query(1,0,size,l,r);
    }
    T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) { //no overlap
            return qn; 
        } 
        if(upd[node]) push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
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

    ll n, q; cin >> n >> q;
    Lazy<ll> lazy(n);

    for(ll i = 0; i < q; i++) {
        ll type; cin >> type;
        if(type == 0) {
            ll l, r, v; cin >> l >> r >> v;
            lazy.update(l-1,r,v);
        } else {
            int l, r; cin >> l >> r;
            cout << lazy.query(l-1,r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}