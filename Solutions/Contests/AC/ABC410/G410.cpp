#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
first step, correctly read the problem
second step, make the observation that we are trying to find the max interval on things and for each chord on the circle, 
we should add 
*/

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
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

    vector<int> a(n * 4, -1);

    for(int i = 0; i < n; i++) {
        int b, c; cin >> b >> c;
        b--; c--;
        if(b > c) swap(b, c);
        a[c] = b;
        a[b + n * 2] = c;

    }

    Tree<int> tree(n * 4);

    int res = 0;

    for(int i = 0; i < n * 4; i++) {
        if(a[i] != -1) {
            int l = a[i];
            int q = tree.query(l + 1, i);
            res = max(res, q + 1);
            tree.update(l, q + 1);
        }
    }

    cout << res << '\n';

    return 0;
}
