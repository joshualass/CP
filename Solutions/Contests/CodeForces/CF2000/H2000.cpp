#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template <typename T, typename D>
std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
    os << '(' << p.first << ", " << p.second << ") ";
    return os;
}

template<typename T>
struct Tree {
    static constexpr T base = 0;
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
            if(curr & 1) { //non
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
    // optional MIQ stuff
    bool cond(T a, T b) {
        // cout << "a : " << a << " b : " << b << '\n';
        return a <= b;
    }
    //find the lowest index and value that satisfy the condition in range [l,r)
    pair<int,T> queryMIQ(T val, int lo, int hi) { //{index, value}
        pair<int,T> ans = _queryMIQ(1, 0, size, lo, hi, val);
        return ans;
    }   
    pair<int,T> _queryMIQ(int idx, int currl, int currr, int &lo, int &hi, T &val) {
        if(currr > lo && currl < hi && cond(val, v[idx])) {
            // cout << "idx : " << idx << '\n';
            if(isLeaf(idx)) return {idx - size, v[idx]};
            int mid = (currl + currr) / 2;
            pair<int,T> p = _queryMIQ(idx * 2, currl, mid, lo, hi, val);
            if(p.first != -1) {
                return p;
            }
            return _queryMIQ(idx * 2 + 1, mid, currr, lo, hi, val);
        } else {
            return {-1,base};
        }
    }
};

const int MAXN = 2e6 + 1;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Tree<int> tree(MAXN);

    int casi; cin >> casi;
    while(casi--) {

        int n; cin >> n;
        set<int> vis;
        set<int> s;

        tree.update(0,MAXN * 2);
        s.insert(0);
        s.insert(MAXN * 2);

        auto insertset = [&](int x) {
            int prev = (*--s.lower_bound(x));
            int after = *s.lower_bound(x);
            tree.update(x, after - x);
            tree.update(prev, x - prev);
            s.insert(x);
            vis.insert(x);
        };

        auto eraseset = [&](int x) {
            int prev = (*--s.lower_bound(x));
            s.erase(x);
            int after = *s.lower_bound(x);
            tree.update(x,0);
            tree.update(prev, after - prev);
        };

        for(int i = 0; i < n; i++) {
            int a; cin >> a;
            insertset(a);
        }

        int m; cin >> m;
        for(int i = 0; i < m; i++) {
            char type; cin >> type;
            int x; cin >> x;
            if(type == '-') {
                eraseset(x);
            } else if(type == '+') {
                insertset(x);
            } else {
                // cout << "k : " << x << " qv : " << tree.queryMIQ(x +1, 0, MAXN) << "\n";
                cout << tree.queryMIQ(x + 1, 0, MAXN).first + 1 << " ";
            }
        }
        cout << '\n';
        for(int x : vis) {
            tree.update(x,0);
        }

    }

    return 0;
}