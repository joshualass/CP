#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
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

    map<int, vector<int>> m;
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        m[x].push_back(i);
    }

    map<int, vector<array<int,4>>> qs;
    for(int i = 0; i < q; i++) {
        int a, b, c, d; cin >> a >> b >> c >> d;
        a--;
        qs[c - 1].push_back({a, b, i, -1});
        qs[d].push_back({a, b, i, 1});
    }

    Tree<int> tree(n);
    vector<int> res(q);

    for(auto [val, es] : qs) {
        while(m.size() && m.begin()->first <= val) {
            for(auto x : m.begin()->second) tree.update(x, 1);
            m.erase(m.begin());
        }
        for(auto e : es) {
            auto [l, r, qid, mul] = e;
            res[qid] += tree.query(l, r) * mul;
        }
    }

    for(int x : res) cout << x << '\n';

    return 0;
}
