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
        return max(val1, val2);
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
    bool cond(T node_val, T query_val) {
        return node_val >= query_val;
    }
    int queryMIQ(T query_val) {
        return _queryMIQ(1,0,size,0,n,query_val);
    }
    int _queryMIQ(int node, int curl, int curr, int targetl, int targetr, T query_val) {
        if(curr <= targetl || curl >= targetr) return n; //no overlap, done
        push_lazy(node, curr - curl); //for lazy tree
        T val = v[node];
        // cout << "node : " << node << " curl : " << curl << " curr : " << curr << " targetl : " << targetl << " targetr : " << targetr << " qval : " << query_val << " val : " << val << '\n';
        if(cond(val, query_val)) { //if there is a node in this range satisfying cond ...
            if(isLeaf(node)) return curl;
            int mid = (curl + curr) / 2;
            int lidx = _queryMIQ(node * 2, curl, mid, targetl, targetr, query_val);
            if(lidx < n) {
                return lidx;
            }
            return _queryMIQ(node * 2 + 1, mid, curr, targetl, targetr, query_val);
        } else {
            return n;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    Lazy<int,int> lazy(500002,0);
    for(int i = 0; i < 500002; i++) {
        lazy.update(i,i+1,i);
    }

    for(int i = 0; i < n; i++) {
        int l, r; cin >> l >> r;
        int lo = lazy.queryMIQ(l), hi = lazy.queryMIQ(r + 1);
        // cout << "lo : " << lo << " hi : " << hi << '\n';
        lazy.update(lo,hi,1);
    }

    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        int x; cin >> x;
        cout << lazy.query(x,x+1) << '\n';
    }

    return 0;
}