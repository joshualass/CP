#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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
template<typename T, typename D>
struct Lazy {
    static constexpr T qn = {0, 0}; // query neutral, when we query, doing the operation with this value won't change our query
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
        return {max(val1[0], val2[0]), max(val1[1], val2[1])};
        // return max(val1, val2);
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] ^= val;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        if(lazy[node]) swap(v[node][0], v[node][1]);
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
        // cout << "upd l : " << l << " r : " << r << " val : " << val << endl;
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

    int n; cin >> n;
    vector<vector<array<int,2>>> adj(n);
    vector<int> start_toggles;
    for(int i = 0; i + 1 < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back({v, i});
        adj[v].push_back({u, i});
        int t; cin >> t;
        if(t) start_toggles.push_back(i);
    }

    int q; cin >> q;
    vector<int> qs(q);
    for(int &x : qs) {
        cin >> x;
        x--;
    }

    auto dfs = [&](auto self, int i, int p, int d, array<int,2> &res) -> void {
        if(d > res[1]) {
            res = {i, d};
        }
        for(auto [c, id] : adj[i]) {
            if(c != p) {
                self(self, c, i, d + 1, res);
            }
        }
    };

    array<int,2> a = {-1,-1}, b = {-1, -1};
    dfs(dfs, 0, -1, 0, a);
    dfs(dfs, a[0], -1, 0, b);

    // cout << "a : " << a << endl;
    // cout << "b : " << b << endl;

    vector<int> res(q);

    auto work = [&](int root) -> void {

        // cout << "root : " << root << endl;

        vector<int> tin(n), tout(n);
        vector<int> edge(n - 1);
        vector<array<int,2>> d(n); //distances in euler time

        int time = 0;

        auto euler = [&](auto self, int i, int p, int dis) -> void {
            tin[i] = time;
            d[time] = {dis, 0};
            time++;
            for(auto [c, eid] : adj[i]) {
                if(c != p) {
                    edge[eid] = c;
                    self(self, c, i, dis + 1);
                }
            }
            tout[i] = time;
        };

        euler(euler, root, -1, 0);

        // cout << "tin : " << tin << endl;
        // cout << "tout : " << tout << endl;
        // cout << "d : " << d << endl;

        Lazy<array<int,2>, int> lazy(d);
        
        auto pt = [&]() -> void {
            for(int i = 0; i < n; i++) cout << lazy.query(i, i + 1) << endl;
        };

        auto toggle = [&](int eid) -> void {
            int x = edge[eid];
            lazy.update(tin[x], tout[x], 1);
        };

        for(int e : start_toggles) toggle(e);

        for(int qq = 0; qq < q; qq++) {
            toggle(qs[qq]);
            int val = lazy.query(0, n)[0];
            // cout << "qq : " << qq << " val : " << val << endl;
            // pt();
            res[qq] = max(res[qq], val);
        }
    };

    work(a[0]);
    work(b[0]);

    for(int x : res) cout << x << '\n';

    return 0;
}
