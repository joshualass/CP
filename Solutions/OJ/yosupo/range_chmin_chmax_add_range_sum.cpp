#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll inf = 1e18;

/*
Segment Tree Beats very good practice

Intuition is that we stop applying updates when a condition is met instead of when the ranges do not overlap. 
*/

int call_cnt = 0;

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = {0, inf, -inf}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {1, 0}; //lazy neutral, applying this value to its node will not change its value
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
        return {val1[0] + val2[0], min(val1[1], val2[1]), max(val1[2], val2[2])};
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        if(val[0] == 0) {
            lazy[node] = val;
        } else {
            lazy[node][1] += val[1];
        }
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        if(lazy[node][0] == 0) {
            v[node] = {lazy[node][1] * size, lazy[node][1], lazy[node][1]};
        } else {
            v[node][0] += size * lazy[node][1];
            v[node][1] += lazy[node][1];
            v[node][2] += lazy[node][1];
        }
    }
    void push_lazy(int node, int size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(int l, int r, int type, ll b, D val) { //[l,r)
        _update(1,0,size,l,r, type, b, val);
    }
    void _update(int node, int currl, int currr, int &targetl, int &targetr, int type, ll b, D val) {
        call_cnt++;
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(type == 0 && v[node][2] <= b || type == 1 && v[node][1] >= b) return;
        if(currl >= targetl && currr <= targetr && (isLeaf(node) || type == 2)) { //complete overlap + terminating conditions. 
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else if((type == 0 || type == 1) && (v[node][1] == v[node][2])) {
            if(type == 0 && val[1] < v[node][1] || type == 1 && val[1] > v[node][1]) lazy_comb(node, val);
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            int mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, type, b, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, type, b, val);
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

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    // int n = 2e5, q = 2e4;
    Lazy<array<ll,3>, array<ll,2>> lazy(n, {0,0,0});

    for(int i = 0; i < n; i++) {
        ll a; cin >> a;
        // ll a = rng() % 20 - 10;
        lazy.update(i, i + 1, 2, a, {1, a});
    }

    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        // int type = rng() % 4;
        // int l = 0, r = i + 1, b = rng() % 20 - 10;
        if(type == 0) {
            ll l, r, b; cin >> l >> r >> b;
            // ll l = rng() % n, r = rng() % n, b = rng() % 20 - 10;
            // if(l > r) swap(l, r);
            // r++;
            lazy.update(l, r, type, b, {0, b});
        } else if(type == 1) {
            ll l, r, b; cin >> l >> r >> b;
            // ll l = rng() % n, r = rng() % n, b = rng() % 20 - 10;
            // if(l > r) swap(l, r);
            // r++;
            lazy.update(l, r, type, b, {0, b});
        } else if(type == 2) {
            ll l, r, b; cin >> l >> r >> b;
            // ll l = rng() % n, r = rng() % n, b = rng() % 20 - 10;
            // if(l > r) swap(l, r);
            // r++;
            lazy.update(l, r, type, b, {1, b});
        } else {
            ll l, r; cin >> l >> r;
            // ll l = rng() % n, r = rng() % n;
            // if(l > r) swap(l, r);
            // r++;
            cout << lazy.query(l,r)[0] << '\n';
        }

        // if(i == 0 || i == 2 || i == 4 || i == 6) {
        //     cout << "printing tree vals for i : " << i << "\n";
        //     for(int j = 0; j < n; j++) cout << lazy.query(j, j + 1)[0] << " \n"[j == n - 1];
        // }

    }

    // cout << "call cnt : " << call_cnt << '\n';

    return 0;
}
