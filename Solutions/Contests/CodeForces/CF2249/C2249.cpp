#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

// T - query val, D - lazy change
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
        v.resize(size * 2);
        lazy.assign(size * 2, ln);
        build(vector<T>(n, def));
    }
    Lazy(vector<T> a) {
        this->n = sz(a);
        this->size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        lazy.assign(size * 2, ln);
        build(a);
    } 
    void build(vector<T> a) {
        for(int i = 0; i < a.size(); i++) v[i + size] = a[i];
        for(int i = size - 1; i >= 1; i--) {
            v[i] = query_comb(v[i * 2], v[i * 2 + 1]);
        }
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
};

void solve() {
    
    int n; cin >> n;
    vector<int> a(n), ia(n);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        a[i] = x;
        ia[x] = i;
    }

    Lazy<int,int> lazy(n * 2);

    for(int i = 0; i < n; i++) {
        int x = a[i];
        int nei = 0;
        if(x + 1 < n && ia[x+1] < i) nei++;
        if(x && ia[x-1] < i) nei++;
        lazy.update(i, i + n, -nei + 1);
    }

    int res = 0;
    for(int i = 0; i < n; i++) {

        // cout << "i : " << i << endl;
        // for(int j = 0; j < n; j++) {
        //     cout << lazy.query(i + j, i + j + 1) << " ";
        // }
        // cout << endl;

        if(lazy.query(i, i + n) <= 2) res++;

        int x = a[i];
        int nei = 0;
        if(x + 1 < n && ia[x+1] < i) nei++;
        if(x && ia[x-1] < i) nei++;
        lazy.update(i, i + n, -1);
        // lazy.update(i, i + n, -(-nei + 1));

        //always the case that this guy is used.
        if(x + 1 < n) {
            int idx = ia[x + 1];
            if(idx < i) idx += n;
            lazy.update(idx, min(2 * n, idx + n), 1);
        }
        if(x) {
            int idx = ia[x - 1];
            if(idx < i) idx += n;
            lazy.update(idx, min(2 * n, idx + n), 1);
        }

        nei = 2;
        if(x == 0) nei--;
        if(x == n - 1) nei--;

        lazy.update(i + n, n * 2, -nei + 1);
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