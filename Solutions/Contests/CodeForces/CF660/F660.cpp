#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//currently setup for max queries
//y = kx + m
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

    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    ll s = 0, c = accumulate(a.begin(), a.end(), 0LL);
    ll s1 = s;

    for(int i = 0; i < n; i++) {
        s += a[i] * (i + 1);
        s1 += (n - i) * a[i];
    }

    s1 -= c;

    LineContainer lc;
    ll res = 0;
    for(int i = n - 1; i >= 0; i--) {
        ll slope = -c;
        lc.add(slope, s);
        c -= a[i];
        s1 -= c;
        s -= a[i] * (i + 1);
        // cout << "i : " << i << " query : " << lc.query(i) << " s2 : " << s1 << '\n';
        res = max(res, lc.query(i) + s1);
    }

    cout << res << '\n';

    return 0;
}