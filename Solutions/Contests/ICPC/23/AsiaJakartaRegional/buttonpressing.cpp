#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct SegTreeMIQ { //SegTree Minimum Index query. Finds the minimum index that satisfies cond. 
    static constexpr T base = 0; //change this when doing maximum vs minimum etc.
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b; 
    }

    bool cond(T a, T b) { //num, array value
        return b > 0; //change this when doing maximum vs minimum etc.
    }
    vector<T> v;
    int n = -1, size = -1;

    SegTreeMIQ(int n = 0, T def = base) {
        this->n = n; //max number of elements
        this->size = 1 << (31 - __countl_zero(n) - (int)(__builtin_popcount(n) == 1)); //size of vector
        v.assign(size * 2, base);
    }

    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            v[curr/2] = comb(v[curr], v[curr ^ 1]);
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

    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> query(T val, int lo, int hi) {
        if(lo >= hi) return {-1,base}; //starting pos is OOB
        lo = max(lo,0);
        hi = min(hi,n);
        pair<int,T> ans = _query(1, lo, hi, val);
        return ans;
    }   

    pair<int,T> query(T val, int lo) {
        return query(val,lo,n);
    }   

    pair<int,T> query(T val) {
        return query(val, 0, n);
    }

    pair<int,T> _query(int idx, int &lo, int &hi, T &val) {
        //check overlap of left bound
        if(isLeaf(idx)) {
            if(cond(val, v[idx])) { // in case length is 1 and index is invalid
                return {idx - size, v[idx]};
            } else {
                return {-1,base};
            }
        }
        int shift = __countl_zero(idx) - __countl_zero(size);
        int left_lo = (idx << shift) - size;
        int left_hi = left_lo + (1 << (shift - 1));
        int right_lo = left_hi;
        int right_hi = right_lo + (1 << (shift - 1));

        //overlap in left and an answer exists, doesn't necessarily mean a solution
        if(left_hi > lo && cond(val, v[idx * 2])) {
            // cout << " go left \n";
            pair<int,T> ans = _query(idx * 2, lo, hi, val);
            if(ans.first != -1) return ans;
        }
        //overlap in right and an answer exists
        if(right_lo < hi && cond(val, v[idx * 2 + 1])) {
            // cout << " go right \n";
            return _query(idx * 2 + 1, lo, hi, val);
        }

        return {-1,base}; //nooverlap in both sides/doesn't exist
    }
};

int find_idx(string str) {
    int n = str.size();
    SegTreeMIQ<int> tree(n, 0);
    for(int i = 0; i < n; i++) {
        if(str[i] == '1') {
            tree.update(i,1);
        }
    }

    for(int i = 0; i < n; i++) {
        if(tree.at(i) == 1) {
            int next_one = tree.query(0,i+1).first;
            if(next_one == -1) return i;
            tree.update(i,0);
            if(tree.at(i + 1) == 1) { //toggle i + 1 switch, which is already set
                if(i != n - 2) {
                    tree.update(i + 2, tree.at(i + 2) ^ 1);
                }
            } else {
                tree.update(next_one,0);
                if(next_one != n - 1) {
                    tree.update(next_one + 1, tree.at(next_one + 1) ^ 1);
                }
                tree.update(i + 1, 1);
                if(i != n - 2) {
                    tree.update(i + 2, 0);
                }
            }
        }
        // cout << "i : " << i << '\n';
        // cout << "str : ";
        // for(int j = 0; j < n; j++) {
        //     cout << tree.at(j);
        // }
        // cout << '\n';
    }
    return -1; //triggers when 0 1's
}

void solve() {
    int n; cin >> n;

    string a, b; cin >> a >> b;
    int aidx = find_idx(a);
    int bidx = find_idx(b);
    // cout << "aidx : " << aidx << '\n';
    // cout << "bidx : " << bidx << '\n';
    cout << (aidx == bidx || n - aidx - 1 == bidx ? "YES" : "NO") << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}