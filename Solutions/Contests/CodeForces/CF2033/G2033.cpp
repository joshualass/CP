#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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
        v.assign(size * 2, def);
        lazy.assign(size * 2, ln);
    }
    bool isLeaf(int node) {return node >= size;}
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

int lifts[200000][20];

void solve() {
    
    int n; cin >> n;
    vector<vector<int>> adj(n);
    vector<int> d(n);
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    auto buildpars = [&](auto self, int i, int p, int depth) -> void {
        lifts[i][0] = p;
        d[i] = depth;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i, depth + 1);
            }
        }
    };
    buildpars(buildpars, 0, 0, 0);

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[j][i] = lifts[lifts[j][i-1]][i-1];
        }
    }

    auto goupk = [&](int a, int k) -> int {
        for(int i = 0; i < 20; i++) {
            if((k >> i) & 1) {
                a = lifts[a][i];
            }
        }
        return a;
    };

    int q; cin >> q;
    vector<vector<array<int,2>>> queries(n);

    for(int i = 0; i < q; i++) {
        int v, k; cin >> v >> k;
        v--;
        queries[v].push_back({k,i});
    }    

    vector<int> tins(n), touts(n);
    Lazy<int,int> lazy(n);
    int time = 0;

    auto euler_tour = [&](auto self, int i, int p) -> void {
        tins[i] = time++;
        lazy.update(tins[i], tins[i] + 1, d[i]);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
        touts[i] = time;
    };

    euler_tour(euler_tour, 0, -1);

    vector<int> res(q);

    auto dfsqueries = [&](auto self, int i, int p) -> void {
        if(i) {
            lazy.update(tins[i], touts[i], -2);
            lazy.update(0,n,1);
        }
        for(auto [stamina, id] : queries[i]) {
            int kancestor = goupk(i, stamina);
            res[id] = lazy.query(tins[kancestor], touts[kancestor]);
        }
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
        if(i) {
            lazy.update(tins[i], touts[i], 2);
            lazy.update(0,n,-1);
        }
    };

    dfsqueries(dfsqueries, 0, -1);

    for(int i = 0; i < q; i++) {
        cout << res[i] << " \n"[i == q - 1];
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}