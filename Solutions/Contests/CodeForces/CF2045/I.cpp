#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
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

    int n, m; cin >> n >> m;
    vector<int> a(n);
    for(int &x : a) {
        cin >> x;
        x--;    
    }

    vector<vector<int>> ranges(n);
    vector<int> lidx(n,-1);
    ll res = 0;

    vector<vector<int>> validxs(m);
    for(int i = 0; i < n; i++) {
        if(lidx[a[i]] != -1) {
            ranges[lidx[a[i]] + 1].push_back(i);
        } else {
            res += m - 1;
        }
        lidx[a[i]] = i;
        validxs[a[i]].push_back(i);
    }

    Tree<int> tree(n);
    for(int i = 0; i < m; i++) {
        reverse(validxs[i].begin(), validxs[i].end());
        if(validxs[i].size()) {
            tree.update(validxs[i].back(), 1);
        }
    }

    for(int i = 0; i < n; i++) {
        for(int r : ranges[i]) {
            res += tree.query(i, r);
        }
        validxs[a[i]].pop_back();
        if(validxs[a[i]].size()) {
            tree.update(validxs[a[i]].back(), 1);
        }
    }

    cout << res << '\n';

    return 0;
}