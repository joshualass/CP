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

const int hc = 2;
array<ll,hc> P, M;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool isprime(ll num) {
    if(num <= 1) return 0;
    if(num == 2 || num == 3) return 1;
    if(num % 2 == 0 || num % 3 == 0) return 0;
    for(int i = 5; i <= sqrt(num); i++) {
        if(num % i == 0 || num % (i + 2) == 0) return 0;
    }
    return 1;
}

ll gen_prime(ll l, ll r) { //generates a prime number [l,r]
    while(1) {
        ll num = (rng() % (r - l + 1)) + l;
        if(isprime(num)) return num;
    }
}

ll binexp(ll base, ll power, ll mod) {
    ll ans = 1;
    while(power != 0) {
        if(power & 1) {
            ans = ans*base%mod;
        }
        base = base*base%mod;
        power >>= 1;
    }
    return ans;
}

// T - query val, D - lazy change
template<typename T, typename D>
struct Lazy {
    static constexpr T qn = {0,0}; // query neutral, when we query, doing the operation with this value won't change our query
    static constexpr D ln = {1,1}; //lazy neutral, applying this value to its node will not change its value
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
        T res = {};
        for(int i = 0; i < hc; i++) {
            res[i] = (val1[i] + val2[i]) % M[i];
        }
        return res;
    }
    //how we combine lazy updates to lazy
    void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
        for(int i = 0; i < hc; i++) {
            lazy[node][i] = 1LL * lazy[node][i] * val[i] % M[i];
        }
    }
    void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
        for(int i = 0; i < hc; i++) {
            v[node][i] = 1LL * v[node][i] * lazy[node][i] % M[i];
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

// typedef array<int,3> T; T idT = {0,0,0}; // node type
// typedef array<int,3> U; U idU = {1,1,1}; // update type
// // combine segtree nodes a and b
// T f(T a, T b) { 
//     for(int i = 0; i < hc; i++) {
//         a[i] = (a[i] + b[i]) % M[i];
//     }
//     return a;
// }
// // apply updates f and g (f compose g)
// U g(U f, U g) { return f + g; }
// // apply update f to segtree node a
// T h(U f, T a) { return a + f; }
// struct lztree {
// 	int n;
// 	vector<T> t;
// 	vector<U> d;
// 	lztree(int n) : n(n), t(2*n, idT), d(n, idU) {}
// 	void calc(ll p) { t[p] = h(d[p], f(t[p * 2], t[p * 2 + 1])); }
// 	void apply(ll p, U v) {
// 		t[p] = h(v, t[p]);
// 		if(p < n) d[p] = g(v, d[p]);
// 	}
// 	void push(ll p) {
// 		p += n;
// 		for(int s = 24; s > 0; s--) { // need tree height <= 24
// 			ll i = p >> s;
// 			if(d[i] != idU) {
// 				apply(i * 2, d[i]);
// 				apply(i * 2 + 1, d[i]);
// 				d[i] = idU;
// 			}
// 		}
// 	}
// 	void set(ll p, T v) { // point set arr[p] = v
// 		push(p);
// 		t[p += n] = v;
// 		while(p > 1) calc(p /= 2);
// 	}
// 	T get(ll p) { // return arr[p]
//         push(p);
//         return t[p + n];
//     }
// 	void update(ll l, ll r, U v) { // range update [l, r) using v
// 		push(l), push(r - 1);
// 		bool cl = false, cr = false;
// 		for(l += n, r += n; l < r; l /= 2, r /= 2) {
// 			if(cl) calc(l - 1);
// 			if(cr) calc(r);
// 			if(l & 1) apply(l++, v), cl = true;
// 			if(r & 1) apply(--r, v), cr = true;
// 		}
// 		for(--l; r; l /= 2, r /= 2) {
// 			if(cl) calc(l);
// 			if(cr) calc(r);
// 		}
// 	}
// 	T query(ll l, ll r) { // range query [l, r)
// 		push(l), push(r - 1);
// 		T resl = idT, resr = idT;
// 		for(l += n, r += n; l < r; l /= 2, r /= 2) {
// 			if(l & 1) resl = f(resl, t[l++]);
// 			if(r & 1) resr = f(t[--r], resr);
// 		}
// 		return f(resl, resr);
// 	}
// };

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int i = 0; i < hc; i++) {
        M[i] = gen_prime(9e8, 10e8);
        P[i] = gen_prime(1, 1000);
    }

    // cout << "M : " << M << endl;
    // cout << "P : " << P << endl;

    int n, q; cin >> n >> q;
    vector<vector<array<int,hc>>> a(2);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        array<int,hc> cur = {};
        for(int j = 0; j < hc; j++) {
            cur[j] = binexp(P[j], x, M[j]);
        }
        a[i & 1].push_back(cur);
        // cout << "i : " << i << " cur : " << cur << endl;
    }

    vector<Lazy<array<int,hc>, array<int,hc>>> ls;
    for(int i = 0; i < 2; i++) {
        ls.push_back(Lazy<array<int,hc>, array<int,hc>>(a[i]));
    }

    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 0) {
            int l, r, v; cin >> l >> r >> v;
            l--;
            array<int,hc> upd = {};
            for(int i = 0; i < hc; i++) {
                upd[i] = binexp(P[i], v, M[i]);
            }
            // cout << "upd : " << upd << endl;
            for(int i = 0; i < 2; i++) {
                int li = (l + 1 - i) / 2;
                int ri = (r + 1 - i) / 2;
                // cout << "i : " << i << " li : " << li << " ri : " << ri << endl;
                ls[i].update(li, ri, upd);
            }
        } else {
            int l, r; cin >> l >> r;
            l--;
            set<array<int,hc>> s;
            for(int i = 0; i < 2; i++) {
                int li = (l + 1 - i) / 2;
                int ri = (r + 1 - i) / 2;
                // cout << "i : " << i << " li : " << li << " ri : " << ri << endl;
                auto val = ls[i].query(li, ri);
                // cout << "val : " << val << endl;
                s.insert(val);
            }
            cout << (sz(s) == 1 ? "YES" : "NO") << '\n';
        }
    }

    return 0;
}
