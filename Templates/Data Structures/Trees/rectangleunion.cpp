const ll MAXN = 2e6 + 2;

// segment tree
pair<ll, ll> tree[MAXN * 4];
ll lazy[MAXN * 4];

pair<ll, ll> merge(pair<ll, ll> a,
                                 pair<ll, ll> b) {
	if (a.first < b.first) { return a; }
	if (a.first > b.first) { return b; }
	return {a.first, a.second + b.second};
}

// pushes lazy updates down to children
void pushdown(ll t) {
	if (lazy[t]) {
		tree[t << 1].first += lazy[t];
		lazy[t << 1] += lazy[t];
		tree[t << 1 | 1].first += lazy[t];
		lazy[t << 1 | 1] += lazy[t];
		lazy[t] = 0;
	}
}

// constructs the segment tree
void build(ll t = 1, ll tl = 0, ll tr = MAXN) {
	if (tl == tr) {
		tree[t] = {0, 1};
		return;
	}

	ll tm = (tl + tr) >> 1;
	build(t << 1, tl, tm);
	build(t << 1 | 1, tm + 1, tr);
	tree[t] = merge(tree[t << 1], tree[t << 1 | 1]);
}

// adds v to indices l to r
void update(ll l, ll r, ll v, ll t = 1, ll tl = 0, ll tr = MAXN) {
	if (r < tl || tr < l) { return; }
	if (l <= tl && tr <= r) {
		tree[t].first += v;
		lazy[t] += v;
		return;
	}
	pushdown(t);

	ll tm = (tl + tr) >> 1;
	update(l, r, v, t << 1, tl, tm);
	update(l, r, v, t << 1 | 1, tm + 1, tr);
	tree[t] = merge(tree[t << 1], tree[t << 1 | 1]);
}

// queries min and count of entire segment tree
// queries min and count of entire segment tree
ll query() {
	// always maintain one element with value of zero
	// so we don't have to check if zero is the minimum
	return MAXN + 1 - tree[1].second;
}