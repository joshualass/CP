#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
idea is no good ft wa 5 (6)
6
4 1
-20 -19
-5 -7
-4 -7
0 -3
-2 -7

*/

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

#define rep(i, a, b) for(ll i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (ll)(x).size()
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;

template <class T> ll sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Poll {
	typedef Poll P;
	T x, y;
	explicit Poll(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in llerval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns poll rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n; cin >> n;
    vector<Poll<ll>> a;
    for(ll i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        a.push_back(Poll<ll>(x, y));
    }

    ll res = 3;

    auto get_d_vec = [&](ll i, ll j) -> array<ll,2> {
        ll dx = a[j].x - a[i].x, dy = a[j].y - a[i].y;
        ll g = gcd(dx, dy);
        dx /= g;
        dy /= g;
        if(dy < 0) {
            dx *= -1;
            dy *= -1;
        }
        if(dx < 0) {
            dx *= -1;
            dy *= -1;
        }
        return {dx, dy};
    };

    auto offset = [&](array<ll,2> d, ll i) -> ll {
        return 1LL * a[i].x * d[1] - 1LL * a[i].y * d[0];
    };

    auto pos = [&](array<ll,2> d, ll i) -> ll {
        return 1LL * a[i].x * d[0] + 1LL * a[i].y * d[1];
    };

    map<array<ll,2>, map<ll,set<ll>>> s;

    for(ll i = 0; i < n; i++) {
        map<array<ll,2>, ll> m;
        for(ll j = 0; j < n; j++) {
            if(j != i) {
                auto d = get_d_vec(i, j);
                s[d][offset(d, i)].insert(i);
            }
        }
    }

    vector<ll> cur_os(n), cur_pos(n);

    auto work = [&](Poll<ll> v, ll p) -> ll {
        ll cw = -1, ccw = -1;
        for(ll i = 0; i < n; i++) {
            Poll<ll> u = a[i] - a[p];
            ll c = v.cross(u);
            if(c == 0) continue;
            if(c < 0) {
                //clockwise
                if(cw == -1 || (a[cw] - a[p]).cross(a[i] - a[p]) > 0) {
                    cw = i;
                }
            } else {
                if(ccw == -1 || (a[ccw] - a[p]).cross(a[i] - a[p]) < 0) {
                    ccw = i;
                }
            }
        }
        // cout << "work called v : " << v << " p : " << p << endl;
        // cout << "cw : " << cw << " ccw : " << ccw << endl;
        return cw != -1 && ccw != -1 && (a[p] - a[ccw]).cross(a[cw] - a[ccw]) >= 0;
    };

    for(auto [d, info] : s) {
        for(ll i = 0; i < n; i++) {
            cur_os[i] = offset(d, i);
            cur_pos[i] = pos(d, i);
        }

        Poll<ll> f(d[0], d[1]);
        Poll<ll> r = f * -1;

        for(auto [os, idxs] : info) {
            res = max(res, min(n, sz(idxs) + 1));
            ll lo_here = -1, hi_here = -1;
            for(ll idx : idxs) {
                if(lo_here == -1 || cur_pos[idx] < cur_pos[lo_here]) lo_here = idx;
                if(hi_here == -1 || cur_pos[idx] > cur_pos[hi_here]) hi_here = idx;
            }

            //solve problem for hi polls
            ll found = work(f, hi_here) || work(r, lo_here);
            if(found) {
                res = max(res, min(n, sz(idxs) + 2));
                // cout << "found for f : " << f << " os : " << os << endl;
                // cout << "lh : " << lo_here << endl;
                // cout << "hh : " << hi_here << endl;

                // cout << "hit os : " << os << endl;
                // cout << "los : " << los << endl;
                // cout << "his : " << his << endl;
            }
        }
    }

    cout << res << '\n';

    return 0;
}
