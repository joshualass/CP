#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()
const int inf = 1e9;

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

// // T - query val, D - lazy change
// template<typename T, typename D>
// struct Lazy {
//     static constexpr T qn = 1000000000; // query neutral, when we query, doing the operation with this value won't change our query
//     static constexpr D ln = 0; //lazy neutral, applying this value to its node will not change its value
//     vector<T> v;      //stores values at each index we are querying for
//     vector<D> lazy;   //stores lazy update values
//     int n, size;
//     //if OJ is not up to date, remove all occurrences of ln
//     Lazy(int n = 0, T def = qn) {
//         this->n = n;
//         this->size = 1;
//         while(size < n) size *= 2;
//         v.resize(size * 2);
//         lazy.assign(size * 2, ln);
//         build(vector<T>(n, def));
//     }
//     Lazy(int n, vector<T> a) {
//         this->n = n;
//         this->size = 1;
//         while(size < n) size *= 2;
//         v.resize(size * 2);
//         lazy.assign(size * 2, ln);
//         build(a);
//     }   
//     void build(vector<T> a) {
//         for(int i = 0; i < a.size(); i++) v[i + size] = a[i];
//         for(int i = size - 1; i >= 1; i--) {
//             v[i] = query_comb(v[i * 2], v[i * 2 + 1]);
//         }
//     }
//     bool isLeaf(int node) {return node >= size;}
//     T query_comb(T val1, T val2) {//update this depending on query type
//         return min(val1, val2);
//     }
//     //how we combine lazy updates to lazy
//     void lazy_comb(int node, D val) {//update this depending on update type. how do we merge the lazy changes?
//         lazy[node] += val;
//     }
//     void main_comb(int node, int size) {//update this depending on query type, how does the lazy value affect value at v for the query?
//         v[node] += lazy[node];
//     }
//     void push_lazy(int node, int size) {
//         main_comb(node, size); //push lazy change to current node
//         if(!isLeaf(node)) {
//             lazy_comb(node * 2, lazy[node]);
//             lazy_comb(node * 2 + 1, lazy[node]);
//         }
//         lazy[node] = ln;
//     }
//     void update(int l, int r, D val) { //[l,r)
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
//     T query(int l, int r) { // [l,r)
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

typedef ll T; T idT = inf; // node type
typedef ll U; U idU = 0; // update type
// combine segtree nodes a and b
T f(T a, T b) { 
    return min(a, b); 
}
// apply updates f and g (f compose g)
U g(U f, U g) { 
    return f + g; 
}
// apply update f to segtree node a
T h(U f, T a) { 
    return a + f; 
}
struct lztree {
	int n;
	vector<T> t;
	vector<U> d;
	lztree(int n) : n(n), t(2*n, 0), d(n, idU) {}
	void calc(ll p) { t[p] = h(d[p], f(t[p * 2], t[p * 2 + 1])); }
	void apply(ll p, U v) {
		t[p] = h(v, t[p]);
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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
    ll query(int l, int r) {
        return query(r) - query(l);
    }
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

ll get_inversions(vector<int> &a, int p) {
    int n = sz(a);
    FT ft(p);

    ll res = 0;
    for(int x : a) {
        res += ft.query(x + 1, p);
        ft.update(x, 1);
    }

    return res;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
}

void solve() {
    
    int n, m; cin >> n >> m;
    set<int> s;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;

    vector<int> c(a.begin(), a.end());
    c.insert(c.begin(), b.begin(), b.end());

    eraseduplicates(c);
    int p = sz(c);

    vector<vector<int>> at(p);
    vector<int> cnts(p);

    // Lazy<int,int> lazy(n + 1, 0);
	
	lztree lazy(n + 1);

    for(int i = 0; i < n; i++) {
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
        at[a[i]].push_back(i);
        lazy.update(i + 1, n + 1, 1);
    }

    for(int i = 0; i < m; i++) {
        b[i] = lower_bound(c.begin(), c.end(), b[i]) - c.begin();
        cnts[b[i]]++;
    }

    ll res = get_inversions(a, p);

    for(int i = 0; i < p; i++) {
        for(int x : at[i]) {
            lazy.update(x + 1, n + 1, -1);
        }
        ll lo = lazy.query(0, n + 1);
        res += lo * cnts[i];
        for(int x : at[i]) {
            lazy.update(0, x + 1, 1);
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