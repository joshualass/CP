#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

struct Info {
    int l, r, all, res;
    Info(): l(0), r(0), all(0), res(0) {}
    Info(int l, int r, int all, int res): l(l), r(r), all(all), res(res) {}
};

Info operator+(Info lhs, Info rhs) {
    Info res;
    res.l = max(lhs.l, lhs.all + rhs.l);
    res.r = max(rhs.r, rhs.all + lhs.r);
    res.all = lhs.all + rhs.all;
    res.res = max({lhs.res, rhs.res, lhs.r + rhs.l});
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

    int n; cin >> n;
    map<int,vector<int>> m;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x].push_back(i);
    }

    vector<int> res(n);
    Tree<Info> tree(n);

    for(int i = 0; i < n; i++) tree.update(i, Info(0, 0, -1, 0));

    for(auto [k, v] : m) {
        // cout << "k : " << k << '\n';
        for(int x : v) tree.update(x, Info(1, 1, 1, 1));
        for(int x : v) {
            res[x] = max(res[x], (tree.query(0, x).r + tree.query(x + 1, n).l) / 2);
            // cout << "x : " << x << " query r : " << tree.query(0, x).r << " query l : " << tree.query(x + 1, n).l << '\n';
        }

    }

    for(int i = 0; i < n; i++) tree.update(i, Info(0, 0, -1, 0));

    for(auto it = m.rbegin(); it != m.rend(); it++) {
        auto [k, v] = *it;
        for(int x : v) tree.update(x, Info(1, 1, 1, 1));
        for(int x : v) res[x] = max(res[x], (tree.query(0, x).r + tree.query(x + 1, n).l + 1) / 2);
    }

    for(int i = 0; i < n; i++) cout << res[i] << " \n"[i == n - 1];

    return 0;
}
