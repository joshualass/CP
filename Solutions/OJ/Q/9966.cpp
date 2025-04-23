#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

struct Line {
    mutable ld k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ld x) const {return p < x; }
};

static const ld inf = 1/.0;
struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    // static const ll inf = LLONG_MAX;
    ld div(ld a, ld b) {
        return a / b;
    }
    bool isect(iterator x, iterator y) {
        if(y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ld k, ld m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if(x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while((y = x) != begin() && (--x)->p >= y->p) 
            isect(x, erase(y));
    }
    ld query(ld x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int n; cin >> n;
    vector<ld> a(n);
    for(ld &x : a) cin >> x;

    LineContainer lc;
    ld res = 0;
    for(int i = n - 1; i >= 0; i--) {
        ld inc = 0;
        if(i != n - 1) {
            inc = lc.query(i + 1);
        }

        ld ev_hit = (i + 1 + inc);
        res = max(res, a[i] * ev_hit);

        lc.add(-a[i], ev_hit * a[i]);

    }

    cout << fixed << setprecision(15) << res << '\n';

    return 0;
}