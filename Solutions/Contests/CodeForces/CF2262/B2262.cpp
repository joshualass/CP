#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

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

void solve() {
    
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    
    vector<int> p(n);
    for(int i = 0; i < n; i++) {
        cin >> p[i];
        p[i]--;
    }

    set<int> s;
    FT ft(n);
    vector<int> res(n);
    for(int i = n - 1; i >= 0; i--) {
        int x = p[i];
        ft.update(x, a[x]);
        int dontadd = 0;
        if(s.lower_bound(x) != s.begin()) {
            auto it = s.lower_bound(x);
            it--;
            int idx = *it;
            ll sum = ft.query(idx, x);
            if(sum >= a[x]) {
                dontadd = 1;
            }
        }

        if(dontadd == 0) {
            s.insert(x);
        }

        for(auto it = s.upper_bound(x); it != s.end(); ) {
            assert(it != s.begin());
            int p_idx = *prev(it);
            ll sum = ft.query(p_idx, *it);
            if(sum < a[*it]) {
                break;
            } else {
                it = s.erase(it);
            }
        }
        // cout << "i : " << i << " s : " << s << endl;
        res[i] = sz(s) - 1;
    }

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