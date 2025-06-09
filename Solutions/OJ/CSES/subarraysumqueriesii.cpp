#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Info {
    ll res, l, r, all;
    Info(): res(0), l(0), r(0), all(0) {}
    Info(ll res, ll l, ll r, ll all): res(res), l(l), r(r), all(all) {}
};

Info operator+(Info lhs, Info rhs) {
    Info res;
    res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
    res.l = max(lhs.l, lhs.all + rhs.l);
    res.r = max(rhs.r, rhs.all + lhs.r);
    res.all = lhs.all + rhs.all;
    return res;
}

template<typename T>
struct Tree {
    T base;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n, T def) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
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
    T at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r) {//queries in range [l,r)
        return _query(1,0,size,l,r);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return v[idx];
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q; cin >> n >> q;
    Tree<Info> tree(n, Info());
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        tree.update(i, Info(x, x, x, x));
    }

    for(int i = 0; i < q; i++) {
        int a, b; cin >> a >> b;
        a--;
        cout << tree.query(a, b).res << '\n';
    }

    return 0;
}
