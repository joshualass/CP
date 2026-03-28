#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
    ll query(int l, int r) {
        return query(r) - query(l);
    }
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    vector<ll> a(n);
    FT ft(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        ft.update(i, a[i]);
    }
    for(int qq = 0; qq < q; qq++) {
        int type; cin >> type;
        if(type == 1) {
            int k, u; cin >> k >> u;
            k--;
            ll delta = u - a[k];
            ft.update(k, delta);
            a[k] = u;
        } else {
            int l, r; cin >> l >> r;
            l--;
            cout << ft.query(l, r) << '\n';
        }
    }

    return 0;
}
