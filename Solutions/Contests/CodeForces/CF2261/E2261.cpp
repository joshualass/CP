#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

typedef int T; T idT = {}; // node type
typedef int U; U idU = {}; // update type
// combine segtree nodes a and b
T f(T a, T b) { 
	return max(a, b);
}
// apply updates f and g (f compose g)
U g(U f, U g) { 
	return f + g; 
}
// apply update f to segtree node a
T h(U f, T a) { 
	return a + f; 
}
struct lztree {
	int n;
	vector<T> t;
	vector<U> d;
	lztree(int n) : n(n), t(2*n, idT), d(n, idU) {}
	void calc(ll p) { t[p] = h(d[p], f(t[p * 2], t[p * 2 + 1])); }
	void apply(ll p, U v) {
		t[p] = h(v, t[p]);
		if(p < n) d[p] = g(v, d[p]);
	}
	void push(ll p) {
		p += n;
		for(int s = 24; s > 0; s--) { // need tree height <= 24
			ll i = p >> s;
			if(d[i] != idU) {
				apply(i * 2, d[i]);
				apply(i * 2 + 1, d[i]);
				d[i] = idU;
			}
		}
	}
	void set(ll p, T v) { // point set arr[p] = v
		push(p);
		t[p += n] = v;
		while(p > 1) calc(p /= 2);
	}
	T get(ll p) { // return arr[p]
        push(p);
        return t[p + n];
    }
	void update(ll l, ll r, U v) { // range update [l, r) using v
		push(l), push(r - 1);
		bool cl = false, cr = false;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(cl) calc(l - 1);
			if(cr) calc(r);
			if(l & 1) apply(l++, v), cl = true;
			if(r & 1) apply(--r, v), cr = true;
		}
		for(--l; r; l /= 2, r /= 2) {
			if(cl) calc(l);
			if(cr) calc(r);
		}
	}
	T query(ll l, ll r) { // range query [l, r)
		push(l), push(r - 1);
		T resl = idT, resr = idT;
		for(l += n, r += n; l < r; l /= 2, r /= 2) {
			if(l & 1) resl = f(resl, t[l++]);
			if(r & 1) resr = f(t[--r], resr);
		}
		return f(resl, resr);
	}
};

map<pair<string,int>, int> dp;
int solve_slow(string s, int ops) {
    if(dp.count({s, ops}) == 0) {
        int res = 0;
        if(ops == 0) {
            for(int i = 0; i < sz(s); i++) {
                int r = i;
                while(r < sz(s) && s[r] == '(') r++;
                res = max(res, r - i);
            }
        } else {
            for(int i = 0; i + 1 < sz(s); i++) {
                if(s.substr(i, 2) == "()") {
                    string t = s;
                    t = "(" + s.substr(0, i) + s.substr(i + 2) + ")";
                    res = max(res, solve_slow(t, ops - 1));
                }
            }
        }
        dp[{s, ops}] = res;
    }
    return dp[{s, ops}];
}

void solve() {
    
    int n, k; cin >> n >> k;
    string s; cin >> s;
    if(k * 2 == n) {
        cout << k << '\n';
        return;
    }

    int res = 0;

    for(int i = 0, r = -1; i <= k; i++) {
        r++;
        while(s[r] != ')') {
            r++;
        }
        res = max(res, k - i + (r - i));
    }

    lztree ttfang(n);

    for(int l = 0, r = 0, cnt = 0, ops = 0, save = 0; l < n; l++) {
        if(l) {
            if(s[l-1] == '(') {
                ttfang.update(l - 1, n, -1);
                // cnt--;
            } else {
                ttfang.update(l - 1, n, 1);
                ops--;
            }
        }
        while(r < n && (ops < k || ops == k && s[r] == '(')) {
            if(s[r] == '(') {
                ttfang.update(r, n, 1);
                // cnt++;
            } else {
                ttfang.update(r, n, -1);
                ops++;
            }
            // res = max(res, cnt - ops);
            r++;
        }
        // cout << "l : " << l << " r : " << r << " cnt : " << cnt << " ops : " << ops << endl;
        // res = max(res, cnt - k + min(k, saves[r-1]));
        res = max(res, ttfang.query(l, r));
    }

    // for(int i = 0, r = 0; i < n; i++) {
    //     r = max(r, i);
    //     while(r < n && s[r] == '(') {
    //         r++;
    //     }
    //     res = max(res, r - i);
    // }

    res = min(res, n / 2);

    // if(solve_slow(s, k) != res) {
    //     cout << n << " " << k << endl;
    //     cout << s << endl;

    //     cout << "fast : " << res << endl;
    //     cout << "slow : " << solve_slow(s, k) << endl;
    //     assert(0);
    // }
    cout << res << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}