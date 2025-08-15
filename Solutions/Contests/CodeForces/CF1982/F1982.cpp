#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct MaxTree {
    static constexpr T base = INT_MIN;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
    }
    MaxTree(int n = 0, T def = base) {
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
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
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
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node >= query_val;
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
        if(cr <= tl || cl >= tr) return {n, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != n){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {n, base};
        }
    }
};

template<typename T>
struct MinTree {
    static constexpr T base = INT_MAX;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    MinTree(int n = 0, T def = base) {
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
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
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
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node <= query_val;
    }
    pair<int,T> find_last(int l, int r, T query_val) {
        return _find_last(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
            if(p.first != -1) {
                return p;
            }
            return _find_last(idx * 2, cl, mid, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
};

void solve() {
    
    int n; cin >> n;
    MaxTree<int> maxt(n);
    MinTree<int> mint(n);
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
        maxt.update(i, x);
        mint.update(i, x);
    }

    priority_queue<array<int,2>, vector<array<int,2>>, greater<array<int,2>>> minpq;
    priority_queue<array<int,2>> maxpq;

    auto update = [&](int idx) -> void {
        if(idx && a[idx-1] > a[idx]) minpq.push({a[idx], idx});
        if(idx + 1 < n && a[idx+1] < a[idx]) maxpq.push({a[idx], idx});
    };

    for(int i = 0; i < n; i++) update(i);

    auto work = [&]() -> void {

        while(minpq.size()) {
            auto [val, idx] = minpq.top();
            if(val == a[idx] && a[idx] < a[idx-1]) break;
            minpq.pop();
        }

        while(maxpq.size()) {
            auto [val, idx] = maxpq.top();
            if(val == a[idx] && a[idx] > a[idx+1]) break;
            maxpq.pop();
        }

        if(minpq.empty()) {
            cout << "-1 -1\n";
            return;
        }

        int minval = minpq.top()[0];
        int l = maxt.find_first(0, n, minval + 1).first;
        int maxval = maxpq.top()[0];
        int r = mint.find_last(0, n, maxval - 1).first;

        cout << l + 1 << " " << r + 1 << '\n';

    };

    work();

    int q; cin >> q;
    for(int qq = 0; qq < q; qq++) {
        int pos, val; cin >> pos >> val;
        pos--;
        a[pos] = val;
        mint.update(pos, val);
        maxt.update(pos, val);
        for(int j = -1; j <= 1; j++) {
            if(pos + j >= 0 && pos + j < n) update(pos + j);
        }
        work();
    }

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}