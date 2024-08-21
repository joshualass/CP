#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
observations
Both edges of a drawn triangle should touch a point. Otherwise, we could decrease l.
If we want to consider drawing any triangle, we want to always choose the maximum, but also the A * l must be smaller than the sum of the elements inside.
Most useful observation, when we choose to draw a triangle, we won't draw a triangle for the points that are within the box formed by the triangle. 

Use some sort of min lazy segtree to solve this. We will try and solve for all points right of every x for every x. 
To solve for the current x, we will do a 

Each node in lazy segtree represents the cost to erase all the points >= x.
The values stored in each node in the lazy segtree store the minimum cost if we add a triangle from the current x to that point + the remaining cost. 

One thing missed while implementing is that when calculating the minimum and using the triangle that ends at the ex coordinate, it's easy to implement
by using the information of the previous coordinate's minimum. To calcualte if triangle is 0 area/l. 

We add a to all the x's > than current x. We also add a cost to all x's less than k - y because then the triangle won't include. 

*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = INT_MAX; // query neutral, when we query, doing the operation with this value won't change our query
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
        // return val1 + val2;
        return min(val1, val2);
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k, a; cin >> n >> k >> a;
    Lazy<ll,ll> lazy(k+1, 0);

    vector<vector<array<ll,2>>> pts(k+1);
    for(int i = 0; i < n; i++) {
        ll x, y, c; cin >> x >> y >> c;
        pts[x].push_back({y,c});
    }

    vector<ll> s(k+1);
    ll res = 0;

    for(int x = k - 1; x >= 0; x--) {
        //add A to all coords x + 1
        lazy.update(x, x + 1, res);
        lazy.update(x + 1, k + 1, a);

        //add pts
        for(auto [y, c] : pts[x]) {
            lazy.update(x, k - y, c);
        }

        res = lazy.query(x, k + 1);

        lazy.update(x, x + 1, res - lazy.query(x, x + 1));
        s[x] = res;

    }

    cout << lazy.query(0,1) << '\n';

    return 0;
}