#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
        k *= -1;
        m *= -1;
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return (l.k * x + l.m) * -1;
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    n--;
    vector<array<ll,4>> starts(1e6+1,{-1,-1,-1,-1});
    vector<array<ll,3>> stops(1e6+1,{-1,-1,-1});

    for(int i = 0; i < m; i++) {
        ll a, b, s, e; cin >> a >> b >> s >> e;
        a--; b--;
        starts[s] = {a,b,s,e};
    }

    vector<LineContainer> linecontainers(n+1);
    vector<int> vis(2e5);
    vis[0] = 1;
    linecontainers[0].add(0,0);

    ll res = LLONG_MAX;

    for(int i = 0; i <= 1e6; i++) {
        if(starts[i] != array<ll,4>{-1,-1,-1,-1}) {
            auto [a,b,s,e] = starts[i];
            if(vis[a]) {
                ll f = linecontainers[a].query(s) + s * s;
                // cout << "a : " << a << " b : " << b << " s : " << s << " e : " << e << " f : " << f << '\n';
                stops[e] = {-2*e,f+e*e,b};
                if(b == n) {
                    res = min(res,f);
                }
            }
        }
        if(stops[i] != array<ll,3>{-1,-1,-1}) {
            auto [k,m,b] = stops[i];
            // cout << "adding " << "k : " << k << " m : " << m << " b : " << b << endl;
            linecontainers[b].add(k,m);
            // cout << "success" << endl;
            vis[b] = 1;
        }
    }

    cout << res << '\n';

    return 0;
}