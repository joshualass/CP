#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T>
struct Lazy {
    static constexpr T ln = 0, qn = 0; //stores the starting values at all nodes, 
    vector<T> v;      //stores values at each index we are querying for
    vector<T> lazy;   //stores lazy updates at each node
    vector<bool> upd; //stores at each node, whether there is a lazy update to push
    int n = -1, size = -1;

    Lazy(int n = 0, T def = ln) {
        this->n = n;
        this->size = 1 << (31 - __countl_zero(n) - (int)(__builtin_popcount(n) == 1));
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
        upd.assign(n * 2, 0);
    }

    bool isLeaf(int node) {
        return node >= size;
    }
    //when we are querying or updating values from children, how do we combine?
    T query_comb(T val1, T val2) {
        //update this depending on query type
        return val1 + val2;
    }

    //how we combine lazy updates to lazy
    void lazy_comb(int node, T val) {
        //update this depending on update type
        lazy[node] = lazy[node] + val; 
        upd[node] = 1;
    }

    void main_comb(int node, int size) {
        //update this depending on query type, how does the lazy value affect the query?
        v[node] += lazy[node] * size;

    }

    //to fix :(
    // //pushes lazy update to current node as well as to children
    // void push_lazy(int node, int size) {
    //     if(isLeaf(node)) {
    //         //apply lazy update to current node

    //     }
    //     main_comb(node, size);
    //     if(!isLeaf(node)) {
    //         lazy_comb(node * 2, lazy[node]);
    //         lazy_comb(node * 2 + 1, lazy[node]);
    //     }
    //     lazy[node] = ln;
    //     upd[node] = 0;
    // }

    // void update(int l, int r, T val) {
    //     _update(1,l,r,val);
    // }

    void _update(int node, int &targetl, int &targetr, T &val) {
        int shift {__countl_zero(node) - __countl_zero(size)};
        int currl {(node << shift) - size};
        int currr {currl + (1 << shift)};
        //check overlap
        if (currl >= targetr || currr <= targetl) { //there is no overlap
            return; //do nothing if there is no overlap
        }
        if(currl >= targetl && currr <= targetr) { //complete overlap
            //update this node only here
            lazy_comb(node, val);
            push_lazy(node, currr-currl);
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            //update child nodes
            if(upd[node]) {
                push_lazy(node,currr-currl);
            }
            //call child nodes now
            _update(node * 2, targetl, targetr, val);
            _update(node * 2 + 1, targetl, targetr, val);
            //update this node after updating child nodes
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }

    T query(int l, int r) {
        return _query(1,l,r);
    }

    T _query(int node, int &targetl, int &targetr) {
        int shift {__countl_zero(node) - __countl_zero(size)};
        int currl {(node << shift) - size};
        int currr {currl + (1 << shift)};
        //check overlap
        if(currr <= targetl || currl >= targetr) { //no overlap
            return qn; 
        } 
        if(upd[node]) push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            return query_comb(
                _query(node * 2, targetl, targetr),
                _query(node * 2 + 1, targetl, targetr)
            );
        }
    }

};

void solve() {
    int n, q; cin >> n >> q;
    Lazy<ll> lazy(n);
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 0) {
            ll p, q, v; cin >> p >> q >> v;
            lazy.update(p,q+1,v);
            cout << "v : \n" << lazy.v;
            cout << "lazy : \n" << lazy.lazy;
        } else if(type == 1) {
            ll p, q; cin >> p >> q;
            cout << lazy.query(p, q + 1) << '\n';
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}