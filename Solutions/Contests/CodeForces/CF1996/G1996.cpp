#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = {MOD, 0}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
    vector<T> v;      //stores values at each index we are querying for
    vector<D> lazy;   //stores lazy update values
    int n, size;
    //if OJ is not up to date, remove all occurrences of ln
    Lazy(int n = 0) {
        this->n = n;
        this->size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, qn);
        lazy.assign(size * 2, ln);
        for(int i = size * 2 - 1; i > 0; i--) {
            if(isLeaf(i)) {
                v[i] = {0,1};
            } else {
                v[i] = {0, v[i * 2][1] + v[i * 2 + 1][1]};
            }
        }
    }
    bool isLeaf(int node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        if(val1[0] < val2[0]) {
            return val1;
        } else if(val1[0] == val2[0]) {
            return {val1[0], val1[1] + val2[1]};
        } else {
            return val2;
        }
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        // v[node] = {v[node][0] + lazy[node], size};
        v[node][0] += lazy[node];
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
    
    int n, m; cin >> n >> m;

    Lazy<array<int,2>, int> lazy(n * 2);

    vector<vector<array<int,2>>> eventincludes(n * 2); //based on 
    vector<vector<array<int,2>>> eventexcludes(n * 2);

    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        //can use bridge a - b when left point is >= a and right point is <= b
        eventincludes[b].push_back({a,b});
        eventexcludes[a+1].push_back({a,b});

        eventincludes[a+n].push_back({b,a+n});
        eventexcludes[b+1].push_back({b,a+n});

        eventincludes[b+n].push_back({a+n,b+n});
        eventexcludes[a+n+1].push_back({a+n,b+n});
        
    }

    int res = n - 1;

    for(int hi = 0; hi < n * 2; hi++) {
        int lo = hi - n + 1;
        for(array<int,2> x : eventincludes[hi]) {
            // cout << "add range [l,r) " << x << '\n';
            lazy.update(x[0], x[1], 1);
        }
        if(lo >= 0) {
            for(array<int,2> x : eventexcludes[lo]) {
                // cout << "minus range [l,r) " << x << '\n';
                lazy.update(x[0], x[1], -1);
            }
            array<int,2> queryval = lazy.query(lo,hi);
            // cout << "lo : " << lo << " hi : " << hi << " query val : " << queryval << '\n';
            if(queryval[0] == 0) {
                // cout << "update bc it's 0\n";
                res = min(res, n - 1 - lazy.query(lo, hi)[1]);
            }
        }
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