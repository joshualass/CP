#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

typedef ll T; T idT = {}; // node type
typedef array<ll,2> U; U idU = {}; // update type
// combine segtree nodes a and b
T f(T a, T b) { 
    return a + b;
}
// apply updates f and g (f compose g)
U g(U f, U g) { 
    if(f[0]) {
        return f;
    } else {
        g[1] += f[1];
        return g;
    }
}
// apply update f to segtree node a with range size s
T h(U f, T a, ll s) { 
    if(f[0]) {
        return f[1] * s;
    }
    return a + f[1] * s;
}
struct lztree {
	int n;
	vector<T> t;
	vector<U> d;
	vector<ll> s;
	lztree(int n) : n(n), t(2*n, idT), d(n, idU), s(2*n) {
		for(int i = n; i < 2*n; i++) s[i] = 1;
		for(int i = n-1; i; i--) s[i] = s[i*2] + s[i*2+1];
	}
	void calc(ll p) { t[p] = h(d[p], f(t[p * 2], t[p * 2 + 1]), s[p]); }
	void apply(ll p, U v) {
		t[p] = h(v, t[p], s[p]);
		if(p < n) d[p] = g(v, d[p]);
	}
	void push(ll p) {
		p += n;
		for(int s = 24; s > 0; s--) { // need tree height <= 24
			ll i = p >> s;
			if(d[i] != idU) {
				apply(i * 2, d[i]);
				apply(i * 2 + 1, d[i]);
				d[i] = idU;
			}
		}
	}
	void set(ll p, T v) { // point set arr[p] = v
		push(p);
		t[p += n] = v;
		while(p > 1) calc(p /= 2);
	}
	T get(ll p) { // return arr[p]
        push(p);
        return t[p + n];
    }
	void update(ll l, ll r, U v) { // range update [l, r) using v
		push(l), push(r - 1);
		bool cl = false, cr = false;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(cl) calc(l - 1);
			if(cr) calc(r);
			if(l & 1) apply(l++, v), cl = true;
			if(r & 1) apply(--r, v), cr = true;
		}
		for(--l; r; l /= 2, r /= 2) {
			if(cl) calc(l);
			if(cr) calc(r);
		}
	}
	T query(ll l, ll r) { // range query [l, r)
		push(l), push(r - 1);
		T resl = idT, resr = idT;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(l & 1) resl = f(resl, t[l++]);
			if(r & 1) resr = f(t[--r], resr);
		}
		return f(resl, resr);
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;

    lztree lazy(n);

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        lazy.set(i, x);
    }

    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            int l, r, x; cin >> l >> r >> x;
            l--;
            lazy.update(l, r, {0, x});
        } else if(type == 2) {
            int l, r, x; cin >> l >> r >> x;
            l--;
            lazy.update(l, r, {1, x});
        } else {
            int l, r; cin >> l >> r;
            l--;
            cout << lazy.query(l, r) << '\n';
        }
    }

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T, typename D>
// struct Lazy {
//     static constexpr T qn = 0; //stores the starting values at all nodes, 
//     static constexpr D ln = {0,0}; //base, upd type 0 for increment, 1 for assign value
//     vector<T> v;      //stores values at each index we are querying for
//     vector<D> lazy;   //base, count of how many polynomials start at one at the beginning of this node
//     int n, size;

//     //if OJ is not up to date, remove all occurrences of ln
//     Lazy(int n = 0, T def = qn) {
//         this->n = n;
//         this->size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//         lazy.assign(size * 2, ln);
//     }
//     bool isLeaf(int node) {
//         return node >= size;
//     }
//     T query_comb(T val1, T val2) {//update this depending on query type
//         return val1 + val2;
//     }
//     //how we combine lazy updates to lazy
//     void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
//         if(val.second == 0) {
//             lazy[node].first += val.first;
//         } else if(val.second == 1) {
//             lazy[node].first = val.first;
//             lazy[node].second = 1;
//         }
//     }
//     void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
//         if(lazy[node].second == 0) {
//             v[node] += lazy[node].first * size;
//         } else {
//             v[node] = lazy[node].first * size;
//         }
//     }
//     void push_lazy(int node, int size) {
//         main_comb(node, size); //push lazy change to current node
//         if(!isLeaf(node)) {
//             lazy_comb(node * 2, lazy[node]);
//             lazy_comb(node * 2 + 1, lazy[node]);
//         }
//         lazy[node] = ln;
//     }
//     void update(int l, int r, D val) {
//         _update(1,0,size,l,r, val);
//     }
//     void _update(int node, int currl, int currr, int &targetl, int &targetr, D val) {
//         if (currl >= targetr || currr <= targetl) return;
//         push_lazy(node, currr - currl);
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             lazy_comb(node, val); //we apply the lazy change to this node, then update this node.
//         } else { //partial overlap, should never be a leaf, otherwise it'd fall under previous categories 
//             int mid = (currl + currr) / 2;
//             _update(node * 2, currl, mid, targetl, targetr, val);
//             _update(node * 2 + 1, mid, currr, targetl, targetr, val);
//             push_lazy(node * 2, (currr - currl) / 2);
//             push_lazy(node * 2 + 1, (currr - currl) / 2);
//             v[node] = query_comb(v[node * 2], v[node * 2 + 1]);
//         }
//     }
//     T query(int l, int r) {
//         return _query(1,0,size,l,r);
//     }
//     T _query(int node, int currl, int currr, int &targetl, int &targetr) { //[l,r)
//         if(currr <= targetl || currl >= targetr) return qn; 
//         push_lazy(node, currr-currl); //make pushes necessary before getting value, we always check for 2 cases
//         if(currl >= targetl && currr <= targetr) { //complete overlap
//             return v[node];
//         } else {
//             int mid = (currl + currr) / 2;
//             return query_comb(
//                 _query(node * 2, currl, mid, targetl, targetr),
//                 _query(node * 2 + 1, mid, currr, targetl, targetr)
//             );
//         }
//     }
// };

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n, q; cin >> n >> q;
//     Lazy<ll,pair<ll,ll>> lazy(n);
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         lazy.update(i,i+1,{num,0});
//     }

//     for(int i = 0; i < q; i++) {
//         int type; cin >> type;
//         if(type == 1) {
//             int a, b, x; cin >> a >> b >> x;
//             lazy.update(a-1,b,{x,0});
//         }
//         if(type == 2) {
//             int a, b, x; cin >> a >> b >> x;
//             lazy.update(a-1,b,{x,1});
//         }
//         if(type == 3) {
//             int a, b; cin >> a >> b;
//             cout << lazy.query(a-1,b) << '\n';
//         }
//     }

//     return 0;
// }