/*
2026 ICPC Asia Pacific Championship
Problem D
Christmas Tree Un-decoration
*/

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

// T - query val, D - lazy change
template<typename T, typename D>
struct Lazy {
    static constexpr T qn = LLONG_MIN; // query neutral, when we query, doing the operation with this value won't change our query
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

template <bool VALS_EDGES> struct HLD {
	ll N, tim = 0;
	vector<vi> adj;
	vi par, siz, rt, pos, a, chain_len;
	vector<ll> contrib;
	Lazy<ll,ll> *tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1), a(N, 0), chain_len(N, -1),
		  rt(N),pos(N),contrib(N, 0), tree(new Lazy<ll,ll>(N, 0)) { 
			dfsSz(0); dfsHld(0); 
		}
	void dfsSz(ll v) {
		for (ll& u : adj[v]) {
			adj[u].erase(find(all(adj[u]), v));
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(ll v) {
		pos[v] = tim++;
		chain_len[v] = 1;
		for (ll u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
			if(u == adj[v][0]) {
				chain_len[v] = chain_len[u] + 1;
			}
		}
	}
	template <class B> void process(ll u, ll v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v] + 1);
		}
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void update_value(ll u, ll val) {
		// cout << "update called u : " << u << " val : " << val << endl;
		tree->update(pos[u], pos[u] + 1, val - a[u]);
		a[u] = val;
		u = rt[u];
		while(1) {
			ll p = par[u];
			ll nx_contrib = tree->query(pos[u], pos[u] + chain_len[u]);
			// cout << "p : " << p << " nx_contrib : " << nx_contrib << endl;
			if(p != -1) {
				ll hc = adj[p][0];
				// cout << "hc : " << hc << " cur contrib : " << contrib[u] << endl;
				tree->update(pos[hc], pos[hc] + chain_len[hc], nx_contrib - contrib[u]);
			}
			contrib[u] = nx_contrib;
			if(p == -1) break;
			u = rt[p];
		}
	}
	ll query() {
		return contrib[0];
	}
	void print() {
		cout << "par : " << par << endl;
		cout << "siz : " << siz << endl;
		cout << "rt : " << rt << endl;
		cout << "pos : " << pos << endl;
		cout << "a : " << a << endl;
		cout << "chain_len : " << chain_len << endl;
		cout << "contrib : " << contrib << endl;
		cout << "tree vals : ";
		for(int i = 0; i < N; i++) cout << tree->query(i, i + 1) << " ";
		cout << endl;
	}
	// void modifyPath(ll u, ll v, ll val) {
	// 	process(u, v, [&](ll l, ll r) { tree->add(l, r, val); });
	// }
	// ll queryPath(ll u, ll v) { // Modify depending on problemclear
	// 	ll res = -1e9;
	// 	process(u, v, [&](ll l, ll r) {
	// 			res = max(res, tree->query(l, r));
	// 	});
	// 	return res;
	// }
	// ll querySubtree(ll v) { // modifySubtree is similar
	// 	return tree->query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	// }
};

/*
max(ornaments[here], sum of operations needed in all children)
O(N) ez pz
O(n logn * logn)
*/

void solve() {
    
    ll n, q; cin >> n >> q;
	vector<vector<ll>> adj(n);
	for(ll i = 1; i < n; i++) {
		ll p; cin >> p;
		p--;
		adj[p].push_back(i);
		adj[i].push_back(p);
	}
	
	HLD<false> hld(adj);

	// hld.print();

	for(ll i = 0; i < n; i++) {
		ll x; cin >> x;
		hld.update_value(i, x);
		// cout << "update value i : " << i << endl;

		// hld.print();
	}

	cout << hld.query() << '\n';

	for(ll qq = 0; qq < q; qq++) {
		ll u, x; cin >> u >> x;
		u--;
		hld.update_value(u, x);
		cout << hld.query() << '\n';
	}

}



signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}