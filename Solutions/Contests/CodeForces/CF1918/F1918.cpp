#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
We think of this as a cycle problem and the caterpillar has to visit 2n - 2 nodes, but we try to maximize optimizations with trampoline.
We use a greedy approach and create an edge from a leaf to the root that skips the most nodes in our cycle. Then all the edges on that path are visited, so
any skip that skips those edges doesn't provide any additional benefit.
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T, typename D>
struct Lazy {
    static constexpr T qn = {0,-1}; // query neutral, when we query, doing the operation with this value won't change our query
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
    void assign(vector<T> &start) { //nice way to build segtree from vector
        assert(start.size() == n);
        for(int i = 0; i < n; i++) {
            v[i + size] = start[i];
        }
        for(int i = size - 1; i >= 1; i--) {
            v[i] = query_comb(v[i * 2], v[i * 2 + 1]);
        }
    }
    bool isLeaf(int node) {return node >= size;}
    T query_comb(T val1, T val2) {//update this depending on query type
        
        if(val1[0] > val2[0]) {
            return val1;
        } else {
            return val2;
        }

    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        lazy[node] += val;
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        // v[node] += lazy[node];
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<vector<int>> children(n);
    vector<int> pars(n,-1);

    for(int i = 1; i < n; i++) {
        int p; cin >> p;
        p--;
        children[p].push_back(i);
        pars[i] = p;
    }

    vector<int> tin(n,-1), tout(n,-1), atidx(n,-1), depth(n,-1);
    int time = 0;

    auto eulertour = [&](auto self, int i, int d) -> void {
        tin[i] = time;
        atidx[time] = i;
        depth[i] = d;
        time++;

        for(int c : children[i]) {
            self(self, c, d + 1);
        }

        tout[i] = time;

    };

    eulertour(eulertour, 0, 0);

    // cout << "tin : " << tin << '\n';
    // cout << "tout : " << tout << '\n';
    // cout << "atidx : " << atidx << '\n';
    // cout << "depth : " << depth << '\n';

    Lazy<array<int,2>, int> lazy(n);

    vector<array<int,2>> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = {depth[atidx[i]], i};
    }

    lazy.assign(a);
    int savysoda = 0;

    vector<int> vis(n);

    for(int i = 0; i < k + 1; i++) {
        auto [maxpath, idx] = lazy.query(0,n);

        if(maxpath > 0) {
            savysoda += maxpath;
            int trueidx = atidx[idx];

            while(trueidx && vis[trueidx] == 0) {
                vis[trueidx] = 1;
                lazy.update(tin[trueidx], tout[trueidx], -2);
                trueidx = pars[trueidx];
            }   

        } else {
            break;
        }

    }

    cout << (n - 1) * 2 - savysoda << '\n';

    return 0;
}