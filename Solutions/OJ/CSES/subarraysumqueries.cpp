#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    T base = {0,0,0,0};
    vector<T> v;
    T goooooon;
    int n, size;
    void comb(T a, T b) { //change this when doing maximum vs minimum etc.
        ll sum = a[0] + b[0];
        ll pref_max = max(a[1], a[0] + b[1]);
        ll suff_max = max(b[2], b[0] + a[2]);
        ll internal_max = max({a[3],b[3],a[2] + b[1]});
        goooooon[0] = sum;
        goooooon[1] = pref_max;
        goooooon[2] = suff_max;
        goooooon[3] = internal_max;
    }
    // optional MIQ stuff
    bool cond(T a, T b) {
        return a <= b;
    }
    Tree(int n = 0) {
        goooooon.assign(4,0);
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
            if(curr & 1) {
                comb(v[curr ^ 1], v[curr]);
            } else {
                comb(v[curr], v[curr ^ 1]);
            }
            swap(v[curr/2],goooooon);
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
    
    int n, m; cin >> n >> m;
    Tree<vector<ll>> tree(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        tree.update(i,{num,max(0,num),max(0,num),max(0,num)});
    }

    for(int i = 0; i < m; i++) {
        int k, x; cin >> k >> x;
        tree.update(k-1,{x,max(0,x),max(0,x),max(0,x)});
        cout << tree.v[1][3] << '\n';
    }

    return 0;
}