//currently setup for max queries
//y = kx + m
struct Line {
	mutable ll k, m, p, id;
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
	void add(ll k, ll m, ll id) {
		auto z = insert({k, m, 0, id}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	Line query(ll x) {
		assert(!empty());
		auto l0 = lower_bound(x);
		if(l0 != begin()) {
			auto l1 = l0--;
			auto line0 = *l0
			auto line1 = *l1;
			if(line0.k * x + line0.m == line1.k * x + line1.m && line0.id < line1.id) {
				return line0;
			}
			return line1;
		}
		return *l0;
	}
};