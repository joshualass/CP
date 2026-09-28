#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto x : v) os << x << " ";
    return os;
}

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

template<typename T>
struct MaxTree {
    static constexpr T base = INT_MIN;
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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    vector<int> p(n,-1);
    vector<array<int,2>> lis(n + 1,{-1,-1}); //lis, id

    for(int i = 0; i < n; i++) {
        int l = 0, r = n - 1;
        while(l != r) {
            int m = (l + r + 1) / 2;
            if(lis[m][0] != -1 && a[i] > lis[m][0]) {
                l = m;
            } else {
                r = m - 1;
            }
        }
        lis[l+1] = {a[i], i};
        if(l != 0) {
            p[i] = lis[l][1];
        }
    }

    MinTree<int> mint(n);
    MaxTree<int> maxt(n);

    for(int i = 0; i < n; i++) {
        mint.update(i,a[i]);
        maxt.update(i,a[i]);
    }

    // cout << "p : " << p << '\n';

    vector<int> lisidx;
    for(int i = n; i >= 0; i--) {
        if(lis[i][0] != -1) {
            int curr = lis[i][1];
            while(curr != -1) {
                lisidx.push_back(curr);
                curr = p[curr];
            }

            break;
        }
    }

    reverse(lisidx.begin(), lisidx.end());
    // cout << "lisidx : " << lisidx << '\n';

    int found = lisidx[0] != 0 || (lisidx.back() != n - 1);    

    //see if we can be found by adjusting lis idx's
    for(int i = 1; i < lisidx.size() - 1; i++) {

        for(int j = lisidx[i-1] + 1; j < lisidx[i]; j++) {
            if(a[j] > a[lisidx[i-1]] && a[j] < a[lisidx[i+1]] - 1) {
                // cout << "found1 : " << i << " " << j << '\n';
                found = 1;
            }
        }

        for(int j = lisidx[i] + 1; j < lisidx[i+1]; j++) {
            if(a[j] > a[lisidx[i-1]] + 1 && a[j] < a[lisidx[i+1]]) {
                // cout << "found2 : " << i << " " << j << '\n';
                found = 1;
            }
        }
    }

    for(int i = 1; i < lisidx.size(); i++) {

        if(lisidx[i] - lisidx[i-1] > 1 && a[lisidx[i]] - a[lisidx[i-1]] > 1) {
            // cout << "found3 : " << i << '\n';
            found = 1;
        }

    }

    if(lisidx.size() >= 2) {
        for(int i = lisidx[0] + 1; i < lisidx[1]; i++) {
            if(a[i] < a[lisidx[1]]) {
                found = 1;
            }
        }
        int x = lisidx.size() - 1;
        for(int i = lisidx[x - 1] + 1; i < lisidx[x]; i++) {
            if(a[i] > a[lisidx[x-1]]) {
                found = 1;
            }
        }
    }

    cout << lisidx.size() + found << '\n';

    return 0;
}