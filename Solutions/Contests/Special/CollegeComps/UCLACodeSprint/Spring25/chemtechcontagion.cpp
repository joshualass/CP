#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

struct LCA {
	int T = 0;
	vi time, path, ret;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), rmq((dfs(C,0,-1), ret)) {}
	void dfs(vector<vi>& C, int v, int par) {
		time[v] = T++;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}
	//dist(a,b){return depth[a] + depth[b] - 2*depth[lca(a,b)];}
};

struct Tree {
	typedef int T;
	static constexpr T unit = 0;
	T f(T a, T b) { return a + b; } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
    void build (int n) {
        s.assign(n * 2, unit);
        this->n = n;
    }
	void update(int pos, T val) {
		for (s[pos += n] += val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, rt, pos;
	Tree tree;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),
		  rt(N),pos(N) { dfsSz(0); dfsHld(0); tree.build(N);}
	void dfsSz(int v) {
		for (int& u : adj[v]) {
			adj[u].erase(find(all(adj[u]), v));
			par[u] = v;
			dfsSz(u);
			siz[v] += siz[u];
			if (siz[u] > siz[adj[v][0]]) swap(u, adj[v][0]);
		}
	}
	void dfsHld(int v) {
		pos[v] = tim++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfsHld(u);
		}
	}
	template <class B> void process(int u, int v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v] + 1);
		}
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	void modifyPath(int u, int v, int val) {
		process(u, v, [&](int l, int r) { tree.update(l, val); });
	}
	int queryPath(int u, int v) { // Modify depending on problem
		int res = 0;
		process(u, v, [&](int l, int r) {
				res += tree.query(l, r);
		});
		return res;
	}
	int querySubtree(int v) { // modifySubtree is similar
		return tree.query(pos[v] + VALS_EDGES, pos[v] + siz[v]);
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

    // Node test(0, 4);
    // test.add(0,2,1);
    // test.add(1,3,10);
    // test.add(2,4,100);

    // cout << test.query(0, 2) << '\n';
    // cout << test.query(1, 3) << '\n';
    // cout << test.query(2, 4) << '\n';

    int n, m, q; cin >> n >> m >> q;

    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    LCA lca(adj);

    vector<vector<int>> type_a(n); //children
    vector<vector<int>> type_b(n); //other 

    HLD<false> hld0(adj);
    HLD<false> hlda(adj);
    HLD<false> hldb(adj);

    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        int l = lca.lca(u, v);
        if(l == u) {
            type_a[u].push_back(v);
            hlda.modifyPath(v, v, 1);
        } else if(l == v) {
            type_a[v].push_back(u);
            hlda.modifyPath(u, u, 1);
        } else {
            type_b[u].push_back(v);
            type_b[v].push_back(u);
        }

        hld0.modifyPath(u, u, 1);
        hld0.modifyPath(v, v, 1);

    }

    vector<vector<array<int,3>>> q_lca(n);
    vector<vector<array<int,2>>> q_adj(n);

    vector<int> q_ends_on_path(q); //stores counts of endpoints of edges on this path

    for(int i = 0; i < q; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        q_lca[lca.lca(u, v)].push_back({u, v, i});
        q_adj[u].push_back({v, i});
        q_adj[v].push_back({u, i});

        q_ends_on_path[i] = hld0.queryPath(u, v);
    }

    // cout << "q_ends : " << q_ends_on_path << '\n';

    // cout << "what is in hld?\n";
    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " hld[i] : " << hld0.queryPath(i, i) << '\n';
    // }

    vector<int> acnts(q);

    auto dfsa = [&](auto self, int i, int p) -> void {
        //first iterate over all queries with this lca
        for(auto [u, v, id] : q_lca[i]) {
            acnts[id] = hlda.queryPath(u, v);
        }

        //then remove these children
        for(int c : type_a[i]) {
            hlda.modifyPath(c, c, -1);
        }

        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
    };

    dfsa(dfsa, 0, -1);
    // cout << "acnts : " << acnts << '\n';

    vector<int> bcnts(q);

    auto dfsb = [&](auto self, int i, int p) -> void {
        //first add all edges with this of type b
        for(int c : type_b[i]) {
            hldb.modifyPath(c, c, 1);   
        }

        for(auto [v, id] : q_adj[i]) {
            bcnts[id] += hldb.queryPath(i, v);
        }

        for(int c : adj[i]) {
            if(c != p) self(self, c, i);
        }

        for(int c : type_b[i]) {
            hldb.modifyPath(c, c, -1);
        }
    };

    dfsb(dfsb, 0, -1);

    // cout << "bcnts : " << bcnts << '\n';

    for(int i = 0; i < q; i++) {
        cout << q_ends_on_path[i] - acnts[i] * 2 - bcnts[i] << '\n';
    }    


}