#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

char bad = '\0';

struct Info {
    int l, r, all, res;
    char lc, rc, allc;
    Info(): l(0), r(0), all(0), res(0), lc(bad), rc(bad), allc(bad) {}
    Info(int l, char lc, int r, char rc, int all, char allc, int res): l(l), r(r), all(all), res(res), lc(lc), rc(rc), allc(allc) {}
};

Info operator+(Info lhs, Info rhs) {
    Info res;
    res.l = lhs.l;
    if(lhs.allc != bad && lhs.allc == rhs.lc) {
        res.l = lhs.all + rhs.l;
    }
    res.lc = lhs.lc;

    res.r = rhs.r;
    if(rhs.allc != bad && rhs.allc == lhs.rc) {
        res.r = rhs.all + lhs.r;
    }
    res.rc = rhs.rc;

    if(lhs.allc == rhs.allc && lhs.allc != bad) {
        res.allc = lhs.allc;
    }
    res.all = lhs.all + rhs.all;

    res.res = max({lhs.res, rhs.res, res.l, res.r, (lhs.rc == rhs.lc && lhs.rc != bad ? lhs.r + rhs.l : 0)});
    
    return res;
}

Info base;

template<typename T>
struct Tree {
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n, T def = base) {
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

    string s; cin >> s;

    Tree<Info> tree(n);

    for(int i = 0; i < n; i++) {
        tree.update(i, Info(1, s[i], 1, s[i], 1, s[i], 1));
    }

    for(int qq = 0; qq < q; qq++) {
        int t; cin >> t;
        if(t == 1) {
            int i; cin >> i;
            char x; cin >> x;
            i--;
            tree.update(i, Info(1, x, 1, x, 1, x, 1));
        } else {
            int l, r; cin >> l >> r;
            l--;
            cout << tree.query(l, r).res << '\n';
        }
    }

    return 0;
}
