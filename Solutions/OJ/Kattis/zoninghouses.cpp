#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<int, int> pii;

struct MinTree {
    typedef array<int,2> T;
    static constexpr T unit = {INT_MAX, -1};
    T f(T a, T b) {
        return min(a, b);
    }
    vector<T> s; int n;
    MinTree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for( b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

struct MaxTree {
    typedef array<int,2> T;
    static constexpr T unit = {INT_MIN, -1};
    T f(T a, T b) {
        return max(a, b);
    }
    vector<T> s; int n;
    MaxTree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) {
        T ra = unit, rb = unit;
        for( b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int n, q; cin >> n >> q;
    MinTree minx(n), miny(n);
    MaxTree maxx(n), maxy(n);
    vector<array<int,2>> a(n);

    for(int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        a[i] = {x, y};
        minx.update(i, {x, i});
        miny.update(i, {y, i});
        maxx.update(i, {x, i});
        maxy.update(i, {y, i});
    }

    auto test = [&](int l, int r, int rm) -> int {
        minx.update(rm, minx.unit);
        miny.update(rm, miny.unit);
        maxx.update(rm, maxx.unit);
        maxy.update(rm, maxy.unit);

        int xmin = minx.query(l, r)[0];
        int xmax = maxx.query(l, r)[0];
        int ymin = miny.query(l, r)[0];
        int ymax = maxy.query(l, r)[0];

        int res = max(xmax - xmin, ymax - ymin);

        minx.update(rm, {a[rm][0], rm});
        maxx.update(rm, {a[rm][0], rm});
        miny.update(rm ,{a[rm][1], rm});
        maxy.update(rm, {a[rm][1], rm});

        return res;
    };

    for(int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;
        l--;
        int t1 = minx.query(l, r)[1];
        int t2 = maxx.query(l, r)[1];
        int t3 = miny.query(l, r)[1];
        int t4 = maxy.query(l, r)[1];

        cout << min({test(l, r, t1), test(l, r, t2), test(l, r, t3), test(l, r, t4)}) << '\n';

    }

    return 0;
}