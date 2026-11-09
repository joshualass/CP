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
void eraseduplicates(vector<T> &a) {
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
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
    vector<int> a(n);
    for(int &x : a) cin >> x;

    int lo = 0;
    for(int i = 1; i < n; i++) {
        if(a[i] < a[lo]) lo = i;
    }

    if(!is_sorted(a.begin() + lo, a.end())) {
        cout << "-1\n";
        return;
    }

    vector<int> c = a;
    eraseduplicates(c);

    auto compr = [&](int x) -> int {
        return lower_bound(c.begin(), c.end(), x) - c.begin();
    };
    for(int &x : a) x = compr(x);

    // int m = sz(c);
    // FT ft(m);
    // for(int i = lo; i < n; i++) {
    //     ft.update(a[i], 1);
    // }
    // ll ops = 0;
    // for(int i = 0; i < lo; i++) {
    //     ops += ft.query(a[i], m) + 1;
    // }

    // cout << ops << '\n';

    cout << lo << '\n';

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