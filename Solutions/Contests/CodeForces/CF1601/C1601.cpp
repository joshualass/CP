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

// T - query val, D - lazy change
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

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T f(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     }
//     Tree(int n, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] += val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = f(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = f(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return f(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

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

const int maxn = 3e6;
int t[maxn], lazy[maxn];

void push(int v) {
    t[v*2] += lazy[v];
    lazy[v*2] += lazy[v];
    t[v*2+1] += lazy[v];
    lazy[v*2+1] += lazy[v];
    lazy[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int addend) {
    if (l > r) 
        return;
    if (l == tl && tr == r) {
        t[v] += addend;
        lazy[v] += addend;
    } else {
        push(v);
        int tm = (tl + tr) / 2;
        update(v*2, tl, tm, l, min(r, tm), addend);
        update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
        t[v] = max(t[v*2], t[v*2+1]);
    }
}

int query(int v, int tl, int tr, int l, int r) {
    if (l > r)
        return inf;
    if (l == tl && tr == r)
        return t[v];
    push(v);
    int tm = (tl + tr) / 2;
    return min(query(v*2, tl, tm, l, min(r, tm)), 
               query(v*2+1, tm+1, tr, max(l, tm+1), r));
}

void solve() {
    
    int n, m; cin >> n >> m;
    set<int> s;
    vector<int> a(n), b(m);
    for(int &x : a) cin >> x;
    for(int &x : b) cin >> x;
    s.insert(a.begin(), a.end());
    s.insert(b.begin(), b.end());

    map<int,int> cm;
    int p = 0;
    for(int x : s) cm[x] = p++;

    vector<vector<int>> at(p);
    vector<int> cnts(p);

    // Lazy<int,int> lazy(n + 1, 0);
    for(int i = 0; i < (n + 1) * 3; i++) {
        t[i] = 0;
        lazy[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        a[i] = cm[a[i]];
        at[a[i]].push_back(i);
        update(1, i + 1, n + 1, 0, n + 1, 1);
        // lazy.update(i + 1, n + 1, 1);
    }

    for(int i = 0; i < m; i++) {
        cnts[cm[b[i]]]++;
    }

    ll res = get_inversions(a, p);

    for(int i = 0; i < p; i++) {
        for(int x : at[i]) {
            // lazy.update(x + 1, n + 1, -1);
            update(1, x + 1, n + 1, 0, n + 1, -1);
        }
        // ll lo = lazy.query(0, n + 1);
        ll lo = query(1, 0, n + 1, 0, n + 1);
        res += lo * cnts[i];
        for(int x : at[i]) {
            // lazy.update(0, x + 1, 1);
            update(1, 0, x + 1, 0, n + 1, 1);
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