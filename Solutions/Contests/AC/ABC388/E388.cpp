#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct Tree {
    static constexpr T base = INT_MIN;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b);
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
                v[curr / 2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = comb(v[curr], v[curr ^ 1]);
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
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
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    Tree<int> tree(n);
    for(int i = 0; i < n; i++) {
        int lo = -1, hi = i - 1;
        while(lo != hi) {
            int m = (lo + hi + 1) / 2;
            if(a[m] * 2 <= a[i]) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }
        tree.update(i, i - lo);
    }

    // int q; cin >> q;
    // for(int i = 0; i < q; i++) {
        // int l, r; cin >> l >> r;
        // l--; r--;
        int l = 0, r = n - 1;
        int lo = 0, hi = (r - l + 1) / 2;
        while(lo != hi) {
            int m = (lo + hi + 1) / 2;
            int mq = tree.query(r + 1 - m, r + 1);
            int e = r - l + 1 - m * 2;
            // cout << "lo : " << lo << " hi : " << hi << " m : " << m << " mq : " << mq << " e : " << e << '\n';
            if(mq > m + e) {
                hi = m - 1;
            } else {
                lo = m;
            }
        }
        cout << lo << '\n';
    // }

    return 0;
}