#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

const int inf = 1e9;

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
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// T - query val, D - lazy change
struct Lazy {
    typedef array<int,2> T;
    typedef int D;
    static constexpr T qn = {inf, -1}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = -1; //lazy neutral, applying this value to its node will not change its value
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
    Lazy(int n, vector<T> a) {
        this->n = n;
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
        return min(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] = max(lazy[node], val);
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        v[node][0] = max(v[node][0], lazy[node]);
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
    vector<int> a(n), b(n);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<array<int,2>> v(n);
    for(int i = 0; i < n; i++) {
        v[i] = {i, i};
    }

    Lazy lazy(n, v);

    vector<map<int,int>> f(n + 1);
    for(int i = 0; i < n; i++) {
        f[a[i]][i]++;
        f[b[i]][i]++;
    }

    auto pl = [&]() -> void {
        cout << "lazy vals : ";
        for(int i = 0; i < n; i++) cout << lazy.query(i, i + 1) << " ";
        cout << endl;
    };

    // pl();

    ll res = 0;
    for(int i = 0; i <= n; i++) {
        // cout << "i : " << i << endl;
        vector<array<int,2>> c;
        for(auto [k, v] : f[i]) c.push_back({k, v});
        c.push_back({n, 2});

        // cout << "c : " << c << endl;

        for(int j = 0; j < sz(c); j++) {
            auto [idx, cnt] = c[j];
            if(cnt == 1) {
                //kill
                int left = (j ? c[j-1][0] + 1 : 0);
                int nx = (j + 1 < sz(c) ? c[j+1][0] - 1 : n - 1);
                while(1) {
                    auto [mv, mi] = lazy.query(left, idx + 1);
                    if(mv <= nx) {
                        int r = max(idx, mv);
                        res += r - mi;
                        lazy.update(mi, mi + 1, inf);
                    } else {
                        break;
                    }
                }
            } else {
                //expand
                int left = (j ? c[j-1][0] + 1 : 0);
                lazy.update(left, idx, idx);
            }
        }
        // cout << "res : " << res << endl;
        // pl();
    }

    for(int i = 0; i < n; i++) {
        auto [mv, mi] = lazy.query(i, i + 1);
        if(mv != inf) res += n - i;
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