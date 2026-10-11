#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (ll) (x).size()
const int debug = 0;

template<typename T>
ostream& operator<<(ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

struct FT {
	vector<ll> s;
    vector<ll> b;
    FT() {}
	FT(vector<ll> &a, ll l, ll r): b(a.begin() + l, a.begin() + r) {
        s.assign(r - l, 0);
        sort(b.begin(), b.end());
    }
	void _update(ll pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
    void update(ll pos) {
        // cout << "update called with b : " << b << " pos : " << pos << endl;
        _update(lower_bound(b.begin(), b.end(), pos) - b.begin(), 1);
    }
	ll _query(ll pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
    ll query(ll val) {
        return _query(lower_bound(b.begin(), b.end(), val) - b.begin());
    }
};

struct Tree {
    typedef ll T;
    static constexpr T base = {};
    vector<FT> wtf;
    ll n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(vector<T> a) {
        this->n = sz(a); //max number of elements
        size = 1;
        while(size < n) size *= 2;
        wtf.resize(size * 2);
        assert(n == sz(a));
        while(sz(a) != size) a.push_back(-1);
        build(a, 1, 0, size);
    }
    void build(vector<ll> &a, ll cur, ll l, ll r) {
        wtf[cur] = FT(a, l, r);
        if(l + 1 == r) return;
        ll m = (l + r) / 2;
        build(a, cur * 2, l, m);
        build(a, cur * 2 + 1, m, r);
    }
    void update(ll pos, ll val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        ll curr = pos + size;
        while(curr) {
            wtf[curr].update(val);
            curr /= 2;
        }
    }
    T query(ll l, ll r, ll val) {//queries in range [l,r)
        return _query(1,0,size,l,r, val);
    }
    T _query(ll idx, ll currl, ll currr, ll &targetl, ll &targetr, ll val) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return wtf[idx].query(val);
        ll mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr, val),
            _query(idx * 2 + 1, mid, currr, targetl, targetr, val)
        );
    }
};

ll solve(ll n, vector<ll> a, vector<ll> b, vector<ll> c) {
    for(ll &x : a) x--;
    for(ll &x : b) x--;
    for(ll &x : c) x--;

    vector<ll> d(n);
    for(ll i = 0; i < n; i++) {
        d[a[i]] = i;
    }
    for(ll &x : b) x = d[x];
    for(ll &x : c) x = d[x];

    // cout << "tb : " << b << endl;
    // cout << "tc : " << c << endl;

    vector<ll> rc(n);
    for(ll i = 0; i < n; i++) rc[c[i]] = i;

    Tree tree(c);
    ll res = 0;
    for(ll i = 0; i < n; i++) {
        ll x = b[i];
        ll cidx = rc[x];
        ll add = tree.query(0, cidx, x);
        res += add;
        // cout << "i : " << i << " x : " << x << " cidx : " << cidx << " add : " << add << endl;
        tree.update(cidx, x);
    }

    // cout << res << '\n';
    return res;

}

ll solve_slow(ll n, vector<ll> a, vector<ll> b, vector<ll> c) {
    map<array<int,2>, int> m;
    auto work = [&](vector<ll> d) -> void {
        for(int i = 0; i < sz(d); i++) {
            for(int j = i + 1; j < sz(d); j++) {
                m[{d[i],d[j]}]++;
            }
        }
    };
    work(a);
    work(b);
    work(c);
    ll res = 0;
    for(auto [k, v] : m) {
        if(v == 3) res++;
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if(debug == 0) {
        ll n; cin >> n;
        vector<ll> a(n), b(n), c(n);
        for(ll &x : a) cin >> x;
        for(ll &x : b) cin >> x;
        for(ll &x : c) cin >> x;

        cout << solve(n, a, b, c) << '\n';
    
    } else {
        for(int i = 0; i < 1000; i++) {
            // ll n = rng() % 5 + 10;
            ll n = 3;
            vector<ll> a(n), b(n), c(n);
            iota(a.begin(), a.end(), 1LL);
            iota(b.begin(), b.end(), 1LL);
            iota(c.begin(), c.end(), 1LL);

            shuffle(a.begin(), a.end(), rng);
            shuffle(b.begin(), b.end(), rng);
            shuffle(c.begin(), c.end(), rng);

            auto fast = solve(n, a, b, c);
            auto slow = solve_slow(n, a, b, c);

            if(fast != slow) {
                cout << n << endl;
                cout << a << endl;
                cout << b << endl;
                cout << c << endl;
                return 0;
            }
        }
    }


    return 0;
}
