#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

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

// T - query val, D - lazy change
template<typename T, typename D>
struct Lazy {
    static constexpr T qn = {0, 0, 0}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {0, 0}; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    ll n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(ll n = 0, T def = qn) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        lazy.assign(size * 2, ln);
        build(vector<T>(n, def));
    }
    Lazy(ll n, vector<T> a) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        lazy.assign(size * 2, ln);
        build(a);
    }   
    void build(vector<T> a) {
        for(ll i = 0; i < a.size(); i++) v[i + size] = a[i];
        for(ll i = size - 1; i >= 1; i--) {
            v[i] = query_comb(v[i * 2], v[i * 2 + 1]);
        }
    }
    bool isLeaf(ll node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        return T{val1[0] + val2[0], val1[1] + val2[1], max(val1[2], val2[2])};
        // return max(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(ll node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node][0] += val[0];
        if(val[0]) lazy[node][1] = 0;
        lazy[node][1] += val[1];
        // lazy[node] += val;
    }
    void main_comb(ll node, ll size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        if(lazy[node][0] & 1) swap(v[node][0], v[node][1]);
        if(lazy[node][0]) v[node][2] = 0;
        if(v[node][0]) v[node][2] += lazy[node][1];
        // v[node] += lazy[node];
    }
    void push_lazy(ll node, ll size) {
        main_comb(node, size); //push lazy change to current node
        if(!isLeaf(node)) {
            lazy_comb(node * 2, lazy[node]);
            lazy_comb(node * 2 + 1, lazy[node]);
        }
        lazy[node] = ln;
    }
    void update(ll l, ll r, D val) { //[l,r)
        _update(1,0,size,l,r, val);
    }
    void _update(ll node, ll currl, ll currr, ll &targetl, ll &targetr, D val) {
        if (currl >= targetr || currr <= targetl) return;
        push_lazy(node, currr - currl);
        if(currl >= targetl && currr <= targetr) { //complete overlap
            lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
        } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
            ll mid = (currl + currr) / 2;
            _update(node * 2, currl, mid, targetl, targetr, val);
            _update(node * 2 + 1, mid, currr, targetl, targetr, val);
            push_lazy(node * 2, (currr - currl) / 2);
            push_lazy(node * 2 + 1, (currr - currl) / 2);
            v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
        }
    }
    T query(ll l, ll r) { // [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(ll node, ll currl, ll currr, ll &targetl, ll &targetr) { //[l,r)
        if(currr <= targetl || currl >= targetr) return qn; 
        push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
        if(currl >= targetl && currr <= targetr) { //complete overlap
            return v[node];
        } else {
            ll mid = (currl + currr) / 2;
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

    ll n, q; cin >> n >> q;
    vector<array<ll,3>> b(n, {1,0,0});
    Lazy<array<ll,3>,array<ll,2>> lazy(n, b);

    // cout << "v" << endl;
    // cout << lazy.v << endl;

    for(ll qq = 0; qq < q; qq++) {
        ll type; cin >> type;
        if(type == 1) {
            ll l, r, x; cin >> l >> r >> x;
            l--;
            lazy.update(l, r, array<ll,2>{0, x});
        } else if(type == 2) {
            ll l, r; cin >> l >> r;
            l--;
            lazy.update(l, r, array<ll,2>{1, 0});
        } else {
            int l, r; cin >> l >> r;
            l--;
            cout << lazy.query(l, r)[2] << '\n';
        }
    }


    return 0;
}
