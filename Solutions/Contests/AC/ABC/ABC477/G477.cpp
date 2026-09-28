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

/*
there is a nice optimization for this mo's queries on a tree.
we are adding and removing elements many times q sq(n) times and 
we are updating some values and need to find the counts in some range
we are only querying Q times and doing Q * SQ(N) updates. i was originally using a 
ft, having logn cost for both, but this made the update part too expensive. 
one can shift the bottleneck to sqrt decomp on buckets to make the updates O(1) and the 
queries O(sq(N)). then the burden is shifted and overall complexity is O(NSQ(Q)) 
with also building the lca things

algo felt optimal. hard to discern if bald algo or slow impl sometimes ._.
*/

const int MAXN = 200000;
int st[MAXN], en[MAXN], b[MAXN * 2], res[MAXN], active[MAXN], cnts[MAXN];
const int SQ = 450;
int s[SQ * SQ];
int sb[SQ];

void update(int pos, int dif) { // a[pos] += dif
    // for (; pos < MAXN + 1; pos |= pos + 1) s[pos] += dif;
    sb[pos / SQ] += dif;
    s[pos] += dif;
}
int query(int l, int r) {
    int res = 0, cnt = 0;;
    for(int i = 0; i < SQ; i++) {
        int lb = i * SQ, rb = (i + 1) * SQ;
        if(l <= lb && rb <= r) {
            res += sb[i];
        } else if(lb <= l && l < rb || lb < r && r <= rb) {
            cnt++;
            for(int j = max(l, lb); j < min(r, rb); j++) res += s[j];
        }
    }
    assert(cnt <= 2);
    return res;
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
	vi time, path, ret, depth;
	RMQ<int> rmq;

	LCA(vector<vi>& C) : time(sz(C)), depth(sz(C)), rmq((dfs(C,0,-1, 0), ret)) {}
	void dfs(vector<vi>& C, int v, int par, int dep) {
		time[v] = T++;
        depth[v] = dep;
		for (int y : C[v]) if (y != par) {
			path.push_back(v), ret.push_back(time[v]);
			dfs(C, y, v, dep + 1);
		}
	}

	int lca(int a, int b) {
		if (a == b) return a;
		tie(a, b) = minmax(time[a], time[b]);
		return path[rmq.query(a, b)];
	}

    int dist(int a, int b) {
        return depth[a] + depth[b] - 2*depth[lca(a,b)];
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;
    }
    
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // vector<int> st(n), en(n);
    // vector<int> b(n * 2);
    int time = 0;

    auto dfs = [&](auto self, int i, int p) -> void {
        st[i] = time;
        b[time] = i;
        time++;
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
        en[i] = time;
        b[time] = i;
        time++;
    };

    dfs(dfs, 0, -1);

    vector<array<int,6>> qs; // {l, r, a, b, opt add, qid}
    LCA lca(adj);

    for(int qq = 0; qq < q; qq++) {
        int s, t, a, b; cin >> s >> t >> a >> b;
        s--; t--;
        b++;
        if(st[s] > st[t]) {
            swap(s, t);
        }
        if(lca.lca(s, t) == s) {
            qs.push_back({st[s], st[t] + 1, a, b, -1, qq});
        } else {
            qs.push_back({en[s], st[t] + 1, a, b, st[lca.lca(s, t)], qq});
        }
    }

    int SN = sqrt(n);
    sort(qs.begin(), qs.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        int lblock = lhs[0] / SN, rblock = rhs[0] / SN;
        if(lblock == rblock) {
            int lb = lhs[1] / SN, rb = rhs[1] / SN;
            if(lblock % 2 == 0) {
                return lb < rb;
            } else {
                return lb > rb;
            }
        } else {
            return lblock < rblock;
        }
    }); 

    // vector<int> res(q);
    // vector<int> active(n);
    // vector<int> cnts(n);
    // FT ft(n + 1);
    // ft.update(0, n);

    auto toggle = [&](int i) -> void {
        // cout << "toggle i : " << i << endl;
        int x = b[i];
        // cout << "mih -1" << endl;
        int color = a[x];
        // cout << "mih 0" << endl;
        if(cnts[color]) update(cnts[color], -1);
        // cout << "mih 0.1" << endl;
        if(active[x] == 0) {
            cnts[color]++;
        } else {
            cnts[color]--;
        }
        // cout << "mih 1" << endl;
        active[x] ^= 1;
        // cout << "mih 2" << endl;
        if(cnts[color]) update(cnts[color], 1);
    };

    int l = 0, r = 0;
    for(auto [tl, tr, a, b, opt, qid] : qs) {
        // cout << "tl : " << tl << " tr : " << tr << " a : " << a << " b : " << b << " opt : " << opt << " qid : " << qid << endl;
        while(l > tl) {
            toggle(--l);
        }
        while(r < tr) {
            toggle(r++);
        }
        while(l < tl) {
            toggle(l++);
        }
        while(r > tr) {
            toggle(--r);
        }

        if(opt != -1) toggle(opt);
        res[qid] = query(a, b);
        if(opt != -1) toggle(opt);
    }

    // for(int x : res) cout << x << '\n';
    for(int i = 0; i < q; i++) cout << res[i] << '\n';

    return 0;
}
