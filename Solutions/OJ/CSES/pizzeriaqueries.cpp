#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    // for(auto &x : v) os << x << " ";
    // return os;
    for(int i = 1; v.size() >= 1 << i; i++) {
        for(int j = 1 << (i - 1); 1 << i > j; j++) {
            // os << "i : " << i << " j : " << j << ' ';
            os << v[j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = INT_MAX;
    vector<T> v; //store distance from node 0
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a,b); 
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
        v[curr] = val + pos;
        while(curr != 1) {
            if(curr & 1) { //non
                v[curr/2] = comb(v[curr ^ 1], v[curr]);
            } else {
                v[curr/2] = comb(v[curr], v[curr ^ 1]);
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q; cin >> n >> q;
    Tree<int> pre(n);
    Tree<int> suff(n);
    for(int i = 0; i < n; i++) {
        int num; cin >> num;
        pre.update(i,num);
        suff.update(n-i-1,num);
    }
    // cout << "pre\n" << pre.v;
    // cout << "suff\n" << suff.v;
    for(int i = 0; i < q; i++) {
        int type; cin >> type;
        if(type == 1) {
            int k, x; cin >> k >> x;
            k--;
            pre.update(k,x);
            suff.update(n-k-1,x);
        }
        if(type == 2) {
            int k; cin >> k;
            k--;
            // cout << "k : " << k << " a : " << pre.query(k,n) << " b : " << -k << " c : " << suff.query(n-k-1,n) << " d : " << -(n - k - 1) << '\n';
            cout << min(pre.query(k,n) - k, suff.query(n-k-1,n) - (n - k - 1)) << '\n';
        }
    }

    return 0;
}