#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class T>
constexpr T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

//Modular Division currently uses Little Fermat's Theorem, so won't work for nonprime p. 
template<int P>
struct Mint {
    int x;
    constexpr Mint(): x{} {}
    constexpr Mint(ll x): x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if(P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if(x < 0) {
            x += getMod();
        }
        if(x >= getMod()) { //not sure why this is needed
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Mint operator-() const {
        Mint res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr Mint inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr Mint &operator*=(Mint rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr Mint &operator+=(Mint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr Mint &operator-=(Mint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr Mint &operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr Mint operator*(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr Mint operator+(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr Mint operator-(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr Mint operator/(Mint lhs, Mint rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, Mint &a) {
        ll v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(Mint lhs, Mint rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(Mint lhs, Mint rhs) {
        return lhs.val() != rhs.val();
    }
};

constexpr int P = 998244353;
using Z = Mint<P>;
// using Z = double;
const int MAXN = 1e6;
Z fact[MAXN + 1], inv_fact[MAXN + 1];

Z choose(int n, int k) {
    if(k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] * inv_fact[n-k];
}

void init_fact(int n = MAXN) {
    fact[0] = Z(1);
    inv_fact[0] = Z(1);
    for(int i = 1; i <= n; i++) {
        fact[i] = fact[i-1] * i;
    }
    inv_fact[n] = 1 / fact[n];
    for(int i = n - 1; i >= 1; i--) {
        inv_fact[i] = inv_fact[i+1] * (i + 1);
    }
}

/*
init_fact()
*/

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

    ll n, seed, m, f; cin >> n >> seed >> m >> f;
    vector<ll> q(m - 1), d(m);
    for(ll &x : q) {
        cin >> x;
        x--;
    }
    for(ll &x : d) {
        cin >> x;
        x--;
    }

    ll state = seed;
    vector<vector<int>> ch(n);
    vector<int> par(n);

    for(int i = 1; i < n; i++) {
        int par;
        if(i < m) {
            par = q[i - 1];
        } else {
            par = state % i;
            state = (state * 1103515245 + 12345) & ((1LL << 31) - 1);
        }
        ch[par].push_back(i);
    }

    vector<ll> col(n);

    for(int i = 0; i < n; i++) {
        if(i < m) {
            col[i] = d[i];
        } else {
            col[i] = state % f;
            state = (state * 1103515245 + 12345) & ((1LL << 31) - 1);
        }
    }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " ch[i] : " << ch[i] << endl;
    // }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " color[i] : " << col[i] << endl;
    // }

    LCA lca(ch);

    vector<vector<array<int,2>>> sts(n);
    vector<vector<int>> mxs(n);

    auto dfs = [&](auto self, int i) -> void {
        int c = col[i];
        if(!sts[c].empty()) {
            int unc = lca.lca(sts[c].back()[0], i);
            int tc = 0;
            while(!sts[c].empty() && lca.depth[sts[c].back()[0]] > lca.depth[unc]) {
                auto [x, cnt] = sts[c].back();
                sts[c].pop_back();
                tc += cnt;
                mxs[x].push_back(tc);
            }
            if(!sts[c].empty() && sts[c].back()[0] == unc) {
                sts[c].back()[1] += tc;
            } else {
                sts[c].push_back({unc, tc});
            }
        }
        sts[c].push_back({i, 1});
        for(int child : ch[i]) self(self, child);
    };

    dfs(dfs, 0);

    for(int i = 0; i < n; i++) {
        int tc = 0;
        while(!sts[i].empty()) {
            tc += sts[i].back()[1];
            mxs[sts[i].back()[0]].push_back(tc);
            sts[i].pop_back();
        }
    }

    // for(int i = 0; i < n; i++) {
    //     cout << "i : " << i << " mxs[i] : " << mxs[i] << endl;
    // }

    Z res = 0;

    auto dfs2 = [&](auto self, int i) -> array<int,2> {
        int mx = -1, freq = 0;
        for(int child : ch[i]) {
            auto [cmx, cfreq] = self(self, child);
            if(cmx > mx) {
                mx = cmx;
                freq = cfreq;
            } else if(cmx == mx) {
                freq += cfreq;
            }
        }
        for(int x : mxs[i]) {
            if(x > mx) {
                mx = x;
                freq = 1;
            } else if(x == mx) {
                freq++;
            }
        }
        // cout << "i : " << i << " mx : " << mx << " freq : " << freq << endl;
        res += 1LL * (mx ^ (i + 1)) * (freq ^ (i + 1));
        return {mx, freq};
    };

    dfs2(dfs2, 0);

    cout << res << '\n';
    
    return 0;
}
