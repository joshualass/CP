// https://open.kattis.com/problems/unrealestate
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

const ll MAXN = 2e5 + 1;

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
ll query() {
	// always maintain one element with value of zero
	// so we don't have to check if zero is the minimum
	return MAXN + 1 - tree[1].second;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n; cin >> n;
    vector<array<ll,4>> events;
    for(int i = 0; i < n; i++) {
        ld X1,Y1,X2,Y2; cin >> X1 >> Y1 >> X2 >> Y2;
        ll x1 = X1 * 100 + 1e5;
        ll y1 = Y1 * 100 + 1e5;
        ll x2 = X2 * 100 + 1e5;
        ll y2 = Y2 * 100 + 1e5 - 1;
        events.push_back({x1,1,y1,y2});
        events.push_back({x2,-1,y1,y2});
    }

    sort(events.begin(), events.end());
    build();
    ld ans = 0;
    ll prev = 0;
    for(int i = 0; i < events.size(); i++) {
        ans += query() * (events[i][0] - prev);
        update(events[i][2],events[i][3],events[i][1]);
        prev = events[i][0];
    }

    cout << fixed << setprecision(2) << ans / 10000 << '\n';

    return 0;
}