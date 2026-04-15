#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

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

    int n, q; cin >> q >> n;
    vector<array<ll,2>> a(n), qs(q); // {position, utility}, workstations
    for(auto &x : qs) for(auto &y : x) cin >> y;
    for(auto &x : a) for(auto &y : x) cin >> y;
    
    vector<ll> res(q, LLONG_MIN);

    auto work = [&]() -> void {
        //{x, type, info}
        vector<array<ll,4>> events;

        // {type = 0, utility, _}
        for(int i = 0; i < n; i++) {
            events.push_back({a[i][0], 0, a[i][1], 0});
        }
        //{type = 1, y, id}
        for(int i = 0; i < q; i++) {
            events.push_back({qs[i][0], 1, qs[i][1], i});
        }

        sort(events.begin(), events.end());

        LineContainer lc;

        for(auto event : events) {
            if(event[1] == 0) {
                lc.add(2 * event[0], event[2] - event[0] * event[0]);
            } else {
                if(sz(lc)) {
                    ll util = lc.query(event[0]) - event[2] * event[2] - event[0] * event[0];
                    res[event[3]] = max(res[event[3]], util);
                }
            }
        }
    };

    work();
    for(auto &x : a) x[0] *= -1;
    for(auto &x : qs) x[0] *= -1;
    work();

    for(int i = 0; i < q; i++) {
        cout << res[i] << " \n"[i == q - 1];
    }

    return 0;
}
