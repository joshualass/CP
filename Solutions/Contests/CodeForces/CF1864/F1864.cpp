#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

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

template<typename T>
struct SumTree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    SumTree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] += val;
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
    
    int n, q; cin >> n >> q;

    vector<vector<int>> idxs(n+1);
    vector<int> p(n+1);
    for(int i = 0; i < n; i++) {
        int a; cin >> a;
        idxs[a].push_back(i);
        p[a]++;
    }

    for(int i = 1; i <= n; i++) {
        p[i] += p[i-1];
    }

    SumTree<int> saves(n+1);
    vector<vector<int>> willsave(n+1);
    Tree<int> tree(n);

    for(int i = 0; i <= n; i++) {
        int previdx = -1;
        for(int idx : idxs[i]) {
            if(previdx != -1) {
                int q = tree.query(previdx + 1, idx);
                if(q == 0) {
                    saves.update(i, 1);
                } else {
                    willsave[q].push_back(i);
                }
            }
            previdx = idx;
            tree.update(idx, i);
        }
    }

    vector<vector<array<int,2>>> queries(n + 1);

    for(int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        queries[l].push_back({r,i});
    }

    vector<int> res(q);

    for(int i = 1; i <= n; i++) {
        for(int add : willsave[i - 1]) {
            saves.update(add, 1);
        }

        for(array<int,2> query : queries[i]) {
            int elements = p[query[0]] - p[i-1];
            int totalsaved = saves.query(i, query[0] + 1);
            res[query[1]] = elements - totalsaved;
        }

    }

    for(int i = 0; i < q; i++) {
        cout << res[i] << '\n';
    }

    return 0;
}