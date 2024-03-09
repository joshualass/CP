#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

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
struct Tree { //SegTree Minimum Index query. Finds the minimum index that satisfies cond. 
    static constexpr T base = {1,0}; //{a,b}
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        // cout << "comb a : " << a << " b : " << b << " ans : " << make_pair(a.first * b.first % MOD, (a.second * b.first + b.second) % MOD) << '\n';
        return {a.first * b.first % MOD, (a.second * b.first + b.second) % MOD};
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
            int lo = min(curr, curr ^ 1);
            int hi = max(curr, curr ^ 1);
            v[curr/2] = comb(v[lo], v[hi]);
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
    // optional MIQ stuff
    bool cond(T a, T b) { //num, array value
        return a <= b; //change this when doing maximum vs minimum etc.
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
    Tree<pair<ll,ll>> tree(n);
    for(int i = 0; i < n; i++) {
        ll a, b; cin >> a >> b;
        tree.update(i,{a,b});
    }
    // cout << "tree start : \n" << tree.v << '\n';
    for(int i = 0; i < q; i++) {
        int type, a, b, c; cin >> type >> a >> b >> c;
        if(type == 0) {
            tree.update(a,{b,c});
        }
        if(type == 1) {
            pair<ll,ll> p = tree.query(a,b);
            // cout << "p : " << p << '\n';
            cout << (c * p.first + p.second) % MOD << '\n';
        }
    }

    return 0;
}