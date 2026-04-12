#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

/*
problem is quite tricky

explored many examples where you can't order by either s or a.

then guess that there exists some ordering such that for all indices i < j, hiker i can never go after hiker j
after finding this ordering, the lazy segtree dp is not as tricky
*/

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

void testing() {

    int n = 4;

    vector<vector<int>> adj(n * n);

    for(int i = 0; i < n * n; i++) {
        for(int j = 0; j < n * n; j++) {
            int a1 = i % n, s1 = i / n % n;
            int a2 = j % n, s2 = j / n % n;
            int ij = s1 < a2;
            int ji = s2 < a1;

            if(ij + ji == 1) {
                if(ij) {
                    adj[i].push_back(j);
                    cout << "i : " << i << " j : " << j << endl;
                } 
            }
        }
    }

    vector<int> ind(n * n);
    for(int i = 0; i < n * n; i++) {
        for(int to : adj[i]) ind[to]++;
    }

    cout << "ind : " << ind << endl;

    queue<int> q;
    vector<int> vis(n * n);
    for(int i = 0; i < n * n; i++) {
        if(ind[i] == 0) q.push(i);
    }

    vector<int> order;

    while(sz(q)) {
        int i = q.front();
        q.pop();
        vis[i] = 1;
        order.push_back(i);
        cout << "vis s : " << i / n % n << " a : " << i % n << endl;
        for(int to : adj[i]) {
            ind[to]--;
            if(ind[to] == 0) {
                q.push(to);
            }
        }
    }

    cout << "vis cnt : " << accumulate(vis.begin(), vis.end(), 0) << '\n';
    cout << "order : " << order << endl;

    int ok = 1;
    for(int k = 0; k < n * n; k++) {
        for(int l = k + 1; l < n * n; l++) {
            int i = order[k], j = order[l];

            int a1 = i % n, s1 = i / n % n;
            int a2 = j % n, s2 = j / n % n;
            int ij = s1 < a2;
            int ji = s2 < a1;
            if(ji && !ij) {
                ok = 0;
                cout << "i : " << k << " j : " << l << endl;
                cout << "a1 : " << a1 << " s1 : " << s1 << endl;
                cout << "a2 : " << a2 << " s2 : " << s2 << endl;
                assert(0);
            }
        }
    }

    cout << "check : " << ok << endl;

}

template<typename T>
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

// T - query val, D - lazy change
template<typename T, typename D>
struct Lazy {
    static constexpr T qn = -inf; // query neutral, when we query, doing the operation with this value won't change our query
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // testing();

    int n, d; cin >> n >> d;
    vector<array<int,2>> a(n);
    vector<int> c;
    for(auto &x : a) {
        for(auto &y : x) {
            cin >> y;
            c.push_back(y);
        }
    }
    c.push_back(d);
    eraseduplicates(c);

    auto cm = [&](int i) -> int {
        return lower_bound(c.begin(), c.end(), i) - c.begin();
    };

    d = cm(d);
    for(auto &x : a) {
        for(auto &y : x) {
            y = cm(y);
        }
    }

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        int sl = lhs[0], al = lhs[1];
        int sr = rhs[0], ar = rhs[1];
        if(min(sl, al) != min(sr, ar)) {
            return min(sl, al) < min(sr, ar);
        }
        if(sl >= al != sr >= ar) {
            return (sl < al) < (sr < ar);
        }
        return sl + al < sr + ar;
    });

    int p = sz(c);

    Lazy<int,int> lazy(p);
    
    auto pl = [&]() -> void {
        cout << "lazy tree status" << endl;
        for(int i = 0; i < p; i++) {
            cout << lazy.query(i, i + 1) << " \n"[i == p - 1];
        }
    };

    // pl();
    
    lazy.update(d, d + 1, inf);

    // cout << "d : " << d << endl;
    // pl();

    for(auto [s, a] : a) {
        // cout << "s : " << s << " a : " << a << endl;
        if(a <= s) {
            //for these choices, it is unchanged
            lazy.update(a, s + 1, 1);
            //we can optionally increase at a
            int v = max(lazy.query(a, a + 1), lazy.query(0, a) + 1);
            lazy.update(a, a + 1, v - lazy.query(a, a + 1));
        } else {
            int v = max(lazy.query(a, a + 1), lazy.query(0, s + 1) + 1);
            lazy.update(a, a + 1, v - lazy.query(a, a + 1));
        }
        // pl();
    }

    cout << lazy.query(0, p) << '\n';

    return 0;
}
