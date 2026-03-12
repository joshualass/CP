#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Node {
    Node *left, *right;
    int val = 0;
    Node(Node *left, Node *right, int val): left(left), right(right), val(val) {}
};

Node* build(int l, int r) {
    if(l + 1 == r) {
        return new Node(nullptr, nullptr, 0);
    }
    int mid = (l + r) / 2;
    return new Node(
        build(l, mid),
        build(mid, r),
        0
    );
}

Node* upd(int l, int r, Node* cur, int u, int x) {
    if(u < l || u >= r) return cur;
    if(u == l && u + 1 == r) {
        return new Node(nullptr, nullptr, x);
    }
    int mid = (l + r) / 2;
    Node* lhs = upd(l, mid, cur->left, u, x);
    Node* rhs = upd(mid, r, cur->right, u, x);
    return new Node(lhs, rhs, lhs->val + rhs->val);
}

int query(int l, int r, Node* cur, int ql, int qr) {
    if(r <= ql || l >= qr) return 0;
    if(ql <= l && r <= qr) return cur->val;
    int mid = (l + r) / 2;
    return query(l, mid, cur->left, ql, qr) + query(mid, r, cur->right, ql, qr);
}

/*
*************************************
need to build sieve --> sieve() 
*************************************
*/
const int N = 1e6 + 1;

int prime_factor[N]; //stores a prime factor of the number. If it is prime, stores itself.
vector <int> prime;

void sieve (int n = N) {
	std::fill (prime_factor, prime_factor + n, -1);
	for (int i = 2; i < n; ++i) {
		if (prime_factor[i] == -1) {
		    prime.push_back(i);
            prime_factor[i] = i;
        }
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			prime_factor[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

void find_divs(int idx, int p, vector<pair<ll,int>> &facts, vector<int> &nums) {
    if(idx == facts.size()) {
        nums.push_back(p);
        return;
    }
    for(int j = 0; j < facts[idx].second + 1; j++) {
        find_divs(idx + 1, p, facts, nums);
        p *= facts[idx].first;
    }
}

void prime_factorize(ll num, vector<pair<ll,int>> &prime_factors) {
    for(int i = 0; i < prime.size() && 1LL * prime[i] * prime[i] <= num; i++) {
        if(num % prime[i] == 0) {
            prime_factors.push_back({prime[i],0});
            while(num % prime[i] == 0) {
                prime_factors.back().second++;
                num /= prime[i];
            }
        }
        while(num < N && num != 1) {
            int t = prime_factor[num];
            prime_factors.push_back({t, 0});
            while(num % t == 0) {
                prime_factors.back().second++;
                num /= t;
            }
        }
    }
    if(num != 1) {
        prime_factors.push_back({num,1});
    }
}

template <bool VALS_EDGES> struct HLD {
	int N, tim = 0;
	vector<vi> adj;
	vi par, siz, rt, pos;
    vector<Node*> roots;
    vector<int> latests;
	HLD(vector<vi> adj_)
		: N(sz(adj_)), adj(adj_), par(N, -1), siz(N, 1),
		  rt(N),pos(N), latests(1000001) { 
            dfsSz(0); dfsHld(0); 
            roots.push_back(build(0, N));
        }
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
    void insert(int u, int x) {
        vector<pair<ll,int>> pf;
        prime_factorize(x, pf);
        for(auto [p, cnt] : pf) {
            roots.push_back(upd(0, N, roots[latests[p]], pos[u], cnt));
            latests[p] = sz(roots) - 1;
        }
        cout << x << " ";
    }
	template <class B> void process(int u, int v, B op) {
		for (;; v = par[rt[v]]) {
			if (pos[u] > pos[v]) swap(u, v);
			if (rt[u] == rt[v]) break;
			op(pos[rt[v]], pos[v] + 1);
		}
		op(pos[u] + VALS_EDGES, pos[v] + 1);
	}
	// void modifyPath(int u, int v, int val) {
	// 	process(u, v, [&](int l, int r) { tree->add(l, r, val); });
	// }
	int queryPath(int u, int v, int a) { // Modify depending on problem
        vector<pair<ll,int>> pf;
        prime_factorize(a, pf);
        for(auto [p, cnt] : pf) {
            int res = 0;
            process(u, v, [&](int l, int r) {
                res +=  query(0, N, roots[latests[p]], l, r);
            });
            for(int i = 0; i < min(res, cnt); i++) a /= p;
        }
        return a;
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    sieve();
    int n, c1; cin >> n >> c1;
    vector<vector<int>> adj(n);
    vector<array<int,3>> ops;
    for(int i = 1; i < n; i++) {
        int a, u, v; cin >> a >> u >> v;
        u--; v--;
        adj[i].push_back(v);
        adj[v].push_back(i);
        ops.push_back({a, u, v});
    }

    HLD<false> hld(adj);
    hld.insert(0, c1);
    for(int i = 0; i < sz(ops); i++) {
        auto [a, u, v] = ops[i];
        a = hld.queryPath(u, v, a);
        hld.insert(i + 1, a);
    }

    cout << '\n';

    return 0;
}
