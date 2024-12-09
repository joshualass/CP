#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

//currently setup for max queries
//y = m + kx
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
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return (l.k * x + l.m);
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<array<ll,2>> a(n);
    for(auto &x : a) cin >> x[0] >> x[1];
    vector<ll> ac(n+1);
    ll d = 0;
    for(ll i = n - 1; i >= 0; i--) {
        d += a[i][1];
        ac[i] = ac[i+1] + d * a[i][0];
    }

    // cout << "ac : " << ac << '\n';

    ll res = LLONG_MAX;
    LineContainer lc;
    ll w = 0, c = 0;
    d = 0;

    for(ll i = 0; i < n; i++) {
        if(i) {
            res = min(res, c - lc.query(d) + ac[i+1]);
        }
        w += a[i][0];
        lc.add(w, -d * w);
        c += a[i][1] * w;
        d += a[i][1];
    }

    cout << res << '\n';

    return 0;
}