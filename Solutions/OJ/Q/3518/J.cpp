#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
J. Jelly Fusion
*/

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
    vector<array<ll,2>> a(n);
    for(auto &x : a) for(auto &y : x) cin >> y;

    ll res = 0;
    
    auto work = [&]() -> void {
        int idx = 0;
        for(int i = 1; i < n; i++) {
            if(a[i][0] > a[idx][0]) idx = i;
        }
        rotate(a.begin(), a.begin() + idx + 1, a.end());
        LineContainer lc0, lc1;
        vector<ll> dp(n + 1), p(n + 1);
        for(int i = 0; i < n; i++) {
            p[i+1] = p[i] + a[i][0] * a[i][1];
            lc0.add(a[i][0], dp[i] + p[i]);
            lc1.add(a[i][1], dp[i] + p[i]);
            dp[i+1] = max(lc0.query(a[i][1]), lc1.query(a[i][0])) - p[i + 1];
        }
        res = max(res, dp[n] + p[n]);
    };

    work();
    reverse(a.begin(), a.end());
    work();

    cout << res << '\n';

    return 0;
}
