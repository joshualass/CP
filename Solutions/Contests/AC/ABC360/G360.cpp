#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct MinTree {
    static constexpr T base = INT_MAX;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a + b);
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

template<typename T>
struct MaxTree {
    static constexpr T base = INT_MIN;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a + b);
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
    n += 2;
    vector<int> a(n);
    for(int i = 1; i <= n; i++) cin >> a[i];
    a[0] = -MOD;
    a[n+1] = MOD;
    vector<int> p(n,-1);
    vector<array<int,2>> lis(n,{-1,-1}); //lis, id

    for(int i = 0; i < n; i++) {
        int l = 0, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(lis[m][0] != -1 && a[i] > lis[m][0]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        lis[l+1] = {a[i], i};
        if(l != 0) {
            p[i] = lis[l][1];
        }
    }

    MinTree<int> mint(n);
    MaxTree<int> maxt(n);

    for(int i = 0; i < n; i++) {
        mint.update(i,a[i]);
        maxt.update(i,a[i]);
    }

    vector<int> lisidx;
    for(int i = n - 1; i >= 0; i--) {
        if(lis[i][0] != -1) {
            int curr = lis[i][1];
            while(curr != -1) {
                lisidx.push_back(curr);
                curr = p[curr];
            }

            break;
        }
    }

    reverse(lisidx.begin(), lisidx.end());
    int lisp = 0;
    for(int i = 0; i < n; i++) {
        if()
    }

    return 0;
}