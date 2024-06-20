#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = -1e18;
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

//update at position i, value v
void upd(Tree<ll> &L, Tree<ll> &R, int n, int i, ll v, ll c) {
    L.update(i,v+i*c);
    R.update(i,v+(n-i-1)*c);
}

//at position i, find highest val from L and R
ll quiero(Tree<ll> &L, Tree<ll> &R, int n, int i, ll c) {
    ll l = L.query(0,i+1) - i * c;
    ll r = R.query(i,n) - (n - i - 1) * c;
    // cout << "c : " << c << " i : " << i << " l : " << l << " r : " << r << '\n';
    return max(l,r);
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, c, m; cin >> n >> c >> m;
    Tree<ll> LTree(n);
    Tree<ll> RTree(n);

    upd(LTree,RTree,n,0,0,c);

    for(int i = 0; i < m; i++) {
        ll t, p; cin >> t >> p;
        t--;
        upd(LTree,RTree,n,t,quiero(LTree,RTree,n,t,c) + p,c);
    }

    ll res = 0;
    for(int i = 0; i < n; i++) {
        res = max(res, LTree.at(i) - i * c);
        res = max(res, RTree.at(i) - (n - i - 1) * c);
    }

    cout << res << '\n';

    return 0;
}