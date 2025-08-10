#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

/*
Observations
For each [l, r] pair, as we increase i, we are increasing minimum candidates 
and decreasing maximum candidates => as we increase i, the score is monotonically decreasing. 
For each [l, r] pair, if this subarray is epic, then there exists a unique lowest i such that the condition is satisfied. 

We solve by iterating over the indices i. 
As i is a leftmost index, either one of the two conditions must be true. 
1) The value at index i is a minimum of all the left elements
 - if we move left, minimum will be larger, so i must be at least to this position. 
2) The value at index i would be a maximum for all the right elements
 - if we move to the left, maximum will be larger, so i must be at least to this position. 
After we fix the i, we will try all the potential maximums that are less than this maximum and minimum ranges. 

amortized because every node has at most on earliest node to its left that is larger. 

if a[i] < a[i+1], then we are not in case 2 ever, so we should only consider case 1, which is a single value
if a[i] > a[i+1], then we should consider the two cases, 

=> doesn't matter the case, we should try both

the cases do not intersect because 

do PIE to implement. 

1
4 3
1 2 1 2


*/

template<typename T>
struct MaxTree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a, b);
    }
    MaxTree(int n = 0, T def = base) {
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
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node >= query_val;
    }
    pair<int,T> find_first(int l, int r, T query_val) {
        return _find_first(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_first(int idx, int cl, int cr, int tl, int tr, T qv) {
        // cout << "idx : " << idx << " cl : " << cl << " cr : " << cr << " tl : " << tl << " tr : " << tr << "\n";
        if(cr <= tl || cl >= tr) return {n, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_first(idx * 2, cl, mid, tl, tr, qv);
            if(p.first != n){
                return p;
            }
            return _find_first(idx * 2 + 1, mid, cr, tl, tr, qv);
        } else {
            return {n, base};
        }
    }
};

template<typename T>
struct MinTree {
    static constexpr T base = INT_MAX;
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a, b);
    }
    MinTree(int n = 0, T def = base) {
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
    bool isLeaf(int idx) {
        return idx >= size;
    }
    bool cond(T query_val, T tree_node) {
        return tree_node <= query_val;
    }
    pair<int,T> find_last(int l, int r, T query_val) {
        return _find_last(1, 0, size, l, r, query_val);
    }
    pair<int,T> _find_last(int idx, int cl, int cr, int tl, int tr, T qv) {
        if(cr <= tl || cl >= tr) return {-1, base};
        if(cond(qv, v[idx])) {
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (cl + cr) / 2;
            auto p = _find_last(idx * 2 + 1, mid, cr, tl, tr, qv);
            if(p.first != -1) {
                return p;
            }
            return _find_last(idx * 2, cl, mid, tl, tr, qv);
        } else {
            return {-1, base};
        }
    }
};

void solve() {
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    MinTree<int> mintree(n);
    MaxTree<int> maxtree(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
        mintree.update(i, x);
        maxtree.update(i, x);
    }

    auto cnt_ways = [&](int i, int lo, int hi) -> ll {
        int hi_len = maxtree.find_first(i + 1, n, hi + 1).first - maxtree.find_first(i + 1, n, hi).first;
        int lo_len = mintree.find_last(0, i + 1, lo).first - mintree.find_last(0, i + 1, lo - 1).first;
        return 1LL * hi_len * lo_len;
    };

    ll res = 0;

    stack<array<int,2>> st;
    for(int i = n - 1; i >= 0; i--) {
        int lo_vis = 0;
        ll here = 0;
        while(st.size() && st.top()[0] < a[i]) {
            auto [val, idx] = st.top();
            st.pop();
            int hi = val, lo = k - val;
            if(lo == a[i]) lo_vis = 1;
            here += cnt_ways(i, lo, hi);
        }

        // cout << "i : " << i << '\n';

        if(lo_vis == 0) {
            int lo_len = i - mintree.find_last(0, i, a[i]).first;
            int lo = a[i], hi = k - a[i];
            int hi_len = maxtree.find_first(i + 1, n, hi + 1).first - maxtree.find_first(i + 1, n, hi).first;
            here += 1LL * lo_len * hi_len;
        }
        
        while(st.size() && st.top()[0] <= a[i]) st.pop();
        st.push({a[i], i});
        res += here;
        // cout << "i : " << i << " here : " << here << '\n';
    }

    cout << res << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}