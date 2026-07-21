#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()

template <typename T, std::size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
    os << "[";
    for (std::size_t i = 0; i < N; ++i) {
        os << arr[i];
        if (i < N - 1) {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

struct Tree {
    typedef ll T;
    static constexpr T base = {};
    vector<T> v;
    ll n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(ll n, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    Tree(vector<T> a) {
        this->n = sz(a); //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.resize(size * 2);
        assert(n == sz(a));
        for(ll i = 0; i < n; i++) {
            v[i + size] = a[i];
        }
        for(ll i = size - 1; i >= 1; i--) {
            v[i] = f(v[i * 2], v[i * 2 + 1]);
        }
    }
    void update(ll pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        ll curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //handles non-communative operations
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    T at(ll idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(ll l, ll r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(ll idx, ll currl, ll currr, ll &targetl, ll &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        ll mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

vector<ll> solve(ll n, ll q, vector<ll> a, vector<array<ll,2>> queries) {

	// cout << n << " " << q << '\n';
	// cout << a << '\n';
	// cout << "huhhh" << endl;
	// cout << queries << endl;

	vector<vector<array<ll,2>>> qs(n);
	for(ll qq = 0; qq < q; qq++) {
		qs[--queries[qq][0]].push_back({queries[qq][1], qq});
	}

    vector<array<ll,2>> segs, spec; //segs and special segments. [l, r]
    vector<ll> resq(q);
	Tree tree(n);

	auto tri = [&](ll x) -> ll {
		return x * (x - 1) / 2;
	};

	auto get_inv = [&](ll prev, ll here, ll start) -> ll {
		if(start) here--;
		ll up = max(0LL, (prev + here) / 2 - prev);
		ll res = (prev + up) * (here - up);
		if(start) here++;
		res -= (prev + here - 1 + prev) * (here) / 2;
		return res;
	};

    for(ll i = n - 1; i >= 0; i--) {
		// cout << "i : " << i << endl;

		ll r = i;
		while(!segs.empty() && a[i] < a[segs.back()[0]]) {
			r = segs.back()[1];
			tree.update(segs.back()[1], 0);
			segs.pop_back();
		}

        while(sz(spec) && spec.back()[1] <= r) {
            spec.pop_back();
        }
        
		segs.push_back({i, r});
        spec.push_back({i, r});

		for(auto it = spec.begin(); it != spec.end(); ) {
			auto [l, r] = *it;
			ll len = r - l + 1;
			if(len <= l - i) {
				tree.update(r, 1LL * len * (len - 1) / 2);
				it = spec.erase(it);
			} else {
				it++;
			}
		}

		for(auto [r, qid] : qs[i]) {
			// cout << "r : " << r << endl;
			ll lo = 0, hi = sz(segs);
			while(lo != hi) {
				ll m = (lo + hi) / 2;
				if(segs[sz(segs) - 1 - m][1] < r) {
					lo = m + 1;
				} else {
					hi = m;
				}
			}
			// cout << "segs : " << segs << endl;
			// cout << "lo : " << lo << endl;
			ll res = tri(r - i);
			// cout << "res start : " << res << endl;
			for(auto sseg : spec) {
				if(sseg[1] < r) {
					// cout << "sseg : " << sseg << endl;
					ll len = sseg[1] - sseg[0] + 1;
					// cout << "slen : " << len << endl;
					if(sseg[0] == i) {
						res += get_inv(sseg[0] - i, len, 1);
					} else {
						res += get_inv(sseg[0] - i, len, 0);
					}
				}
			}
			// cout << "res sub ss : " << res << endl;
			if(lo < sz(segs)) {
				auto s = segs[sz(segs) - 1 - lo];
				res -= tree.query(i, s[0]);
				ll len = r - s[0];
				// cout << "plen : " << len << endl;
				if(s[0] == i) {
					res += get_inv(s[0] - i, len, 1);
				} else {
					res += get_inv(s[0] - i, len, 0);
				}
			} else {
				res -= tree.query(i, n);
			}
			// for(int j = 0; j < n; j++) cout << tree.at(j) << " ";
			// cout << endl;
			// cout << "res w partial : " << res << endl;
			resq[qid] = res;
		}
    }

	// for(ll qq = 0; qq < q; qq++) cout << resq[qq] << '\n';
	return resq;

}

vector<ll> solve_slow(ll n, ll q, vector<ll> a, vector<array<ll,2>> queries) {

	// cout << "testing" << endl;

	// cout << n << " " << q << '\n';
	// cout << a << '\n';
	// cout << queries << endl;

	vector<vector<array<ll,2>>> qs(n);
	for(ll qq = 0; qq < q; qq++) {
		qs[--queries[qq][0]].push_back({queries[qq][1], qq});
	}

	vector<ll> res(q);

	auto work = [&](ll l, ll r) {
		vector<ll> pmin(r - l), pmax(r - l);
		for(ll i = l; i < r; i++) {
			if(i == l) {
				pmin[i - l] = a[i];
				pmax[i - l] = a[i];
			} else {
				pmin[i - l] = min(pmin[i - l - 1], a[i]);
				pmax[i - l] = max(pmax[i - l - 1], a[i]);
			}
		}

		ll res = 0;
		for(ll bm = 0; bm < 1 << (r - l); bm++) {
			vector<ll> b;
			for(ll i = 0; i < r - l; i++) {
				if((bm >> i) & 1) {
					b.push_back(pmin[i]);
				} else {
					b.push_back(pmax[i]);
				}
			}
			ll inv = 0;
			for(ll i = 0; i < r - l; i++) {
				for(ll j = i + 1; j < r - l; j++) {
					if(b[i] > b[j]) inv++;
				}
			}
			res = max(res, inv);
		}
		return res;
	};

	for(ll i = 0; i < n; i++) {
		for(auto [r, qid] : qs[i]) {
			res[qid] = work(i, r);
		}
	}

	return res;
}

const ll debug = 0;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

	if(debug == 0) {
		ll casi; cin >> casi;
		while(casi-->0) {
			ll n, q; cin >> n >> q;
			vector<ll> a(n);
			vector<array<ll,2>> queries(q);
			for(ll &x : a) cin >> x;
			for(auto &x : queries) for(auto &y : x) cin >> y;

			auto res = solve(n, q, a, queries);
			for(auto x : res) cout << x << '\n';
		}
	} else {
		for(ll n = 1; n <= 9; n++) {
			vector<ll> p(n);
			ll q = 0;
			vector<array<ll,2>> queries;
			for(ll i = 1; i <= n; i++) {
				for(ll j = i; j <= n; j++) {
					queries.push_back({i, j});
					q++;
				}
			}

			iota(p.begin(), p.end(), 1);
			
			while(1) {
				auto fast = solve(n, q, p, queries);
				auto slow = solve_slow(n, q, p, queries);
				if(fast != slow) {
					cout << n << " " << q << '\n';
					cout << p << '\n';
					for(auto x : queries) {
						for(auto y : x) cout << y << " ";
						cout << '\n';
					}
					cout << "fast : " << fast << endl;
					cout << "slow : " << slow << endl;
					return 0;
				}
				if(!next_permutation(p.begin(), p.end())) break;
			}
		}

		cout << "all tests passed!" << endl;
	}

    return 0;
}