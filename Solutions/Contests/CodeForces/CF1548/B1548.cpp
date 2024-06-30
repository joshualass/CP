#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

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
    static constexpr T base = -1;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a == -1) return b;
        if(b == -1) return a;
        return gcd(a,b);
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

    bool cond(T val, T condval) {
        return val != condval;
    }

    int rquery(int start, T condval) {
        return _rquery(1, 0, size, start, n, base, condval).second;
    }

    pair<T,int> _rquery(int idx, int currl, int currr, int &targetl, int &targetr, T curr, T &condval) {
        
        if(currr <= targetl || currl >= targetr) return {base,0}; //if there is no overlap, we take no action
        //first check if leaf node
        if(isLeaf(idx)) {
            if(cond(comb(curr,v[idx]), condval)) {
                return {comb(curr,v[idx]), 1};
            } else {
                return {base, 0};
            }
        }
        //next try the entire range
        if(currl >= targetl && currr <= targetr) {//if the entire range is ok, we are ok
            if(cond(comb(curr, v[idx]), condval)) {
                return {comb(curr, v[idx]), currr - currl};
            }
        }
        int mid = (currl + currr) / 2;
        pair<T,int> lhs = _rquery(idx * 2, currl, mid, targetl, targetr, curr, condval);
        // cout << "idx : " << idx << " cl : " << currl << " cr : " << currr << " tl : " << targetl << " tr : " << targetr << " cur : " << curr << '\n';
        // cout << "lhs : " << lhs.first << ", " << lhs.second << '\n';
        if(lhs.second != mid - max(currl,targetl) && mid > targetl) { //check if entire left range is still ok
            return lhs;
        } else { //if it is ok, try right side
            pair<T,int> rhs = _rquery(idx * 2 + 1, mid, currr, targetl, targetr, lhs.first, condval);
            // cout << "idx : " << idx << " cl : " << currl << " cr : " << currr << " tl : " << targetl << " tr : " << targetr << " cur : " << curr << '\n';
            // cout << "rhs : " << rhs.first << ", " << rhs.second << '\n';
            return {comb(lhs.first,rhs.first) ,lhs.second + rhs.second};
        }
    }
};

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;
    Tree<ll> tree(n-1);
    for(int i = 1; i < n; i++) {
        tree.update(i-1,abs(a[i]-a[i-1]));
    }

    // cout << "tree\n" << tree.v << '\n';

    int res = 0;
    for(int i = 0; i < n - 1; i++) {
        res = max(res,tree.rquery(i,1));
    }
    cout << res + 1 << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}