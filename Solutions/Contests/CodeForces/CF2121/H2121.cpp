#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
let each index i in the lazy segment tree store the maximum possible length of a LDS such that its last value is i.
we should maintain that the values of the lazy segment tree are non-decreasing - as we increase the last value of the LDS, the length of the LDS should also increase

transitions for appending a [l, r] segment --- we add 1 to the range [l, r], then apply max operation and max query

*/

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {0, -1}; //lazy neutral, applying this value to its node will not change its value
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
        // return val1 + val2;
        return max(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        //lazy {increase, max}
        //how do we propagate a parent increase and max to a child increase and max?
        
        //apply the increase
        lazy[node][0] += val[0];
        lazy[node][1] += val[0];
        //apply the max
        lazy[node][1] = max(lazy[node][1], val[1]);

    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node] = max(v[node] + lazy[node][0], lazy[node][1]);
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
    vector<int> l(n), r(n);
    set<int> s;
    for(int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        s.insert(l[i]), s.insert(r[i]);
    }
    s.insert(0);
    map<int,int> m;
    int p = 0;
    for(int x : s) m[x] = p++;

    Lazy<ll, array<ll,2>> lazy(m.size());
    for(int i = 0; i < n; i++) {
        lazy.update(m[l[i]], m[r[i]] + 1, array<ll,2>{1, -1});
        lazy.update(m[r[i]] + 1, m.size(), array<ll,2>{0, lazy.query(m[r[i]], m[r[i]] + 1)});
        cout << lazy.query(m.size() - 1, m.size()) << " \n"[i == n - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}