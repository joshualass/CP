#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = 0; //stores the starting values at all nodes, 
    static constexpr D ln = 0;
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //base, count of how many polynomials start at one at the beginning of this node
    int n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {
        return node >= size;
    }
    T query_comb(T val1, T val2) {//update this depending on query type
        return max(val1,val2);
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
    T query(int l, int r) {
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n,q;
    cin >> n >> q;
    vector<ll> a(n),pm(n),sm(n);
    ll sub = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        sub += a[i];
        pm[i] = a[i];
        sm[i] = a[i];
        if(i > 0){
            pm[i] = max(pm[i], pm[i-1]);
        }
    }    
    for(int i = n-2; i >= 0; i--){
        sm[i] = max(sm[i], sm[i+1]);
    }
    Lazy<ll,ll> b(n);
    ll sum = 0;
    for(int i = 0; i < n; i++){
        b.update(i,i + 1,min(pm[i], sm[i]));
        sum += min(pm[i], sm[i]);
    }
    cout << sum - sub << endl;
    while(q--){
        ll x,y;
        cin >> x >> y;
        a[i]
    }


    return 0;
}