#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct MinTree {
    static constexpr T base = 1'000'000;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return min(a,b);
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
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
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
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

template<typename T>
struct MaxTree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        return max(a,b);
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
                v[curr / 2] = f(v[curr ^ 1], v[curr]);
            } else {
                v[curr / 2] = f(v[curr], v[curr ^ 1]);
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
        return f(
            _query(idx * 2, currl, mid, targetl, targetr),
            _query(idx * 2 + 1, mid, currr, targetl, targetr)
        );
    }
};

void solve() {
    
    int n; cin >> n;
    vector<int> a(n);
    for(int &x : a) cin >> x;

    MaxTree<int> maxt(n);
    MinTree<int> mint(n);

    for(int i = 0; i < n; i++) {
        maxt.update(i, a[i]);
        mint.update(i, a[i]);
    }

    deque<int> inc, dec;

    auto add_amt = [&](int idx) -> int {
        int res = 0;
        res += inc.empty() || a[idx] > inc.back();
        res += dec.empty() || a[idx] < dec.back();
        return res;
    };

    auto add = [&](int idx) -> void {
        if(inc.empty() || a[idx] > inc.back()) {
            inc.push_back(a[idx]);
        } else if(inc.size() == 1 || inc[inc.size() - 2] < a[idx]) {
            inc.pop_back();
            inc.push_back(a[idx]);
        }
        if(dec.empty() || a[idx] < dec.back()) {
            dec.push_back(a[idx]);
        } else if(dec.size() == 1 || dec[dec.size() - 2] > a[idx]) {
            dec.pop_back();
            dec.push_back(a[idx]);
        }
    };

    ll res = 0;
    int l = 0;

    for(int r = 0; r < n; r++) {
        while(add_amt(r) + inc.size() + dec.size() != r - l + 2) {
            if(inc.front() == a[l]) inc.pop_front();
            if(dec.front() == a[l]) dec.pop_front();
            l++;
            if(inc.size() == 1) {
                inc.pop_front();
                inc.push_back(mint.query(l, r));
            }
            if(dec.size() == 1) {
                dec.pop_front();
                dec.push_back(maxt.query(l,r));
            }
        }
        add(r);
        // cout << "l : " << l << " r : " << r << '\n';
        res += r - l + 1;
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