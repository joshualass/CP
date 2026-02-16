#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

/*
The 4th Universal Cup. Stage 16: Grand Prix of Warsaw
K. Multiset Variance
*/

struct Line {
    mutable ld k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ld x) const { return p < x; }
};

static const ld inf = 1/.0;
struct LineContainer : multiset<Line, less<>> {
    ld div(ld a, ld b) {
        return a / b;
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if(x->k == y->k) x->p - x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ld k, ld m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while(isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ld query(ld x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return l.k * x + l.m;
    }
};

void solve() {
    int n; cin >> n;
    vector<vector<LineContainer>> lcs(11, vector<LineContainer>(11));
    vector<vector<int>> a(n);
    for(int i = 0; i < n; i++) {
        int k; cin >> k;
        for(int j = 0; j < k; j++) {
            int x; cin >> x;
            a[i].push_back(x);
        }
    }

    ld mn = LLONG_MAX, mx = LLONG_MIN;
    for(int i = 0; i < n; i++) {
        // int k; cin >> k;
        int k = sz(a[i]);
        ld s = 0, t = 0;
        for(int j = 0; j < k; j++) {
            // ll x; cin >> x;
            ll x = a[i][j];
            s += x;
            t += x * x;
        }
        mn = min(mn, t / k - s * s / (k * k));

        ld k2 = k;
        ld s2 = s;
        ld t2 = t;

        for(int k1 = 1; k1 <= 10; k1++) {
            ld const_part = t / (k1 + k2) - (s2 * s2) / ((k1 + k2) * (k1 + k2));
            ld query_at = s2;
            if(lcs[k1][k].size()) {
                ld res = const_part + lcs[k1][k].query(query_at);
                mx = max(mx, res);
            }
        }

        for(int k2 = 1; k2 <= 10; k2++) {
            ld const_part = -(s2 * s2) / ((k + k2) * (k + k2)) + t / (k + k2);
            ld slope = -2 * s / ((k + k2) * (k + k2));
            lcs[k][k2].add(slope, const_part);
        }
    }

    cout << fixed << setprecision(20) << mn << " " << mx << endl;

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int casi; cin >> casi;
    while(casi-->0) solve();  

    return 0;
}