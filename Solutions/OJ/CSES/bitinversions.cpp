#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    T base = {0,0,0,0,0,0,0};
    vector<T> v;
    int n, size;
    void comb(T a, T b, T &c) { //change this when doing maximum vs minimum etc.
        if(a[4]) {
            c[0] = a[0] + b[0];
        } else {
            c[0] = a[0];
        }
        if(a[5]) {
            c[1] = a[1] + b[1];
        } else {
            c[1] = a[1];
        }
        if(b[4]) {
            c[2] = b[2] + a[2];
        } else {
            c[2] = b[2];
        }
        if(b[5]) {
            c[3] = b[3] + a[3];
        } else {
            c[3] = b[3];
        }
        c[4] = a[4] & b[4];
        c[5] = a[5] & b[5];
        c[6] = max({a[6],b[6],a[2] + b[0], a[3] + b[1]});
    }
    // optional MIQ stuff
    bool cond(T a, T b, T &c) {
        return a <= b;
    }
    Tree(int n = 0) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, base);
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) { //non
                // v[curr / 2] = comb(v[curr ^ 1], v[curr]);
                comb(v[curr ^ 1], v[curr], v[curr / 2]);
            } else {
                // v[curr / 2] = comb(v[curr], v[curr ^ 1]);
                comb(v[curr], v[curr ^ 1], v[curr / 2]);
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
    // T query(int l, int r) {//queries in range [l,r)
    //     return _query(1,0,size,l,r);
    // }
    // T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
    //     if(currr <= targetl || currl >= targetr) return base;
    //     if(currl >= targetl && currr <= targetr) return v[idx];
    //     int mid = (currl + currr) / 2;
    //     return comb(
    //         _query(idx * 2, currl, mid, targetl, targetr),
    //         _query(idx * 2 + 1, mid, currr, targetl, targetr)
    //     );
    // }
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s; cin >> s;
    int n = s.size();
    Tree<vector<int>> tree(n);
    for(int i = 0; i < n; i++) {
        if(s[i] == '0') {
            tree.update(i,{1,0,1,0,1,0,1});
        } else {
            tree.update(i,{0,1,0,1,0,1,1});
        }
    }
    int q; cin >> q;
    vector<int> upd(7,1);
    for(int i = 0; i < q; i++) {
        int toggle; cin >> toggle;
        toggle--;
        for(int bit = 0; bit < 6; bit++) {
            upd[bit] = tree.at(toggle)[bit] ^ 1;
        }
        tree.update(toggle,upd);
        cout << tree.v[1][6] << " \n"[i == q - 1];
    }

    return 0;
}