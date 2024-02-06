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
        return a + b;
    }
    // optional MIQ stuff
    bool cond(T a, T b) {
        return a <= b;
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
            if(curr & 1) { //non
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
    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
        pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
        return ans;
    }   
    pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
        //check overlap of left bound
        if(cond(val, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (currl + currr) / 2;
            if(mid > lo && cond(val, v[idx * 2])) return _queryMIQ(idx * 2, currl, mid, lo, hi, val);
            return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
        } else {
            return {-1,base};
        }
    }
};

Tree<int> v[1000];

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    // vector<Tree<int>> v(n,Tree<int>(n));
    for(int i = 0; i < n; i++) {
        v[i].n = n;
        v[i].size = 2048;
        v[i].v.assign(2048 * 2, v[i].base);
        for(int j = 0; j < n; j++) {
            char c; cin >> c;
            if(c == '*') {
                v[i].update(j,1);
            }
        }
    }
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int x, y; cin >> x >> y;
            x--; y--;
            v[x].update(y,v[x].at(y) ^ 1);
        }
        if(type == 2) {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            x1--;
            y1--;
            // x2--;
            // y2--;
            int sum = 0;
            for(int row = x1; row < x2; row++) {
                sum += v[row].query(y1,y2);
            }
            cout << sum << '\n';
        }
    }

    // cout << "OK!\n";

    return 0;
}