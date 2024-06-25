#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template<typename T>
struct Tree {
    static constexpr T base = 0;
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

void solve() {
    ll n, l, r; cin >> n >> l >> r;
    vector<ll> a(n);
    vector<ll> b(n+1);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        b[i+1] = a[i];
        b[i+1] += b[i];
    }

    Tree<int> tree(n+1);
    for(int i = 0; i < n; i++) {
        int lo = i, hi = n;
        while(lo != hi) {
            int m = (lo + hi) / 2;
            if(b[m] - b[i] < l) {
                lo = m + 1;
            } else {
                hi = m;
            }
        }
        // cout << "i : " << i << " lo : " << lo << '\n';
        if(b[lo] - b[i] >= l && b[lo] - b[i] <= r) {
            tree.update(lo-1, 1+tree.query(0,i));
        }
    }
    cout << tree.query(0,n+1) << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}