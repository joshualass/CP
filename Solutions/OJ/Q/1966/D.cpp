#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct Tree {
    static constexpr T base = {INT_MIN, -1};
    vector<set<T>> v;
    int n, size;
    T f(T a, T b) { //change this when doing maximum vs minimum etc.
        if(a[0] > b[0]) return a;
        return b;
    }
    Tree(int n) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {});
    }
    void insert(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr].insert(val);
        while(curr != 1) {
            v[curr / 2].insert(val);
            curr /= 2;
        }
    }
    void erase(int pos, T val) {
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr].erase(val);
        while(curr != 1) {
            v[curr / 2].erase(val);
            curr /= 2;
        }
    }
    T get(int idx, int leq) {
        if(v[idx].upper_bound({leq, INT_MAX}) == v[idx].begin()) return base;
        return *--v[idx].upper_bound({leq, INT_MAX});
    }
    T query(int l, int r, int leq) {//queries in range [l,r)
        return _query(1,0,size,l,r,leq);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr, int leq) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) return get(idx, leq);
        int mid = (currl + currr) / 2;
        return f(
            _query(idx * 2, currl, mid, targetl, targetr, leq),
            _query(idx * 2 + 1, mid, currr, targetl, targetr, leq)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, s; cin >> n >> s;
    vector<array<int,3>> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i][0] >> a[i][1];
        a[i][2] = i;
    }

    sort(a.begin(), a.end(), [&](const auto &lhs, const auto &rhs) -> bool {
        return lhs[1] < rhs[1];
    });

    Tree<array<int,2>> tree(n);
    for(int i = 0; i < n; i++) {
        tree.insert(i, {a[i][0], i});
    }

    vector<int> vis(n);
    vector<array<int,2>> res;
    for(int i = 0; i < n; i++) {
        if(vis[i] == 0) {
            int lo = 0, hi = n;
            while(lo != hi) {
                int m = (lo + hi) / 2;
                if(a[m][1] >= s - a[i][1]) {
                    hi = m;
                } else {
                    lo = m + 1;
                }
            }
            
            tree.erase(i, {a[i][0], i});
            
            auto [l, idx] = tree.query(lo, n, s - a[i][0]);
            if(idx != -1) {
                vis[i] = 1;
                vis[idx] = 1;
                tree.erase(idx, {a[idx][0], idx});
                res.push_back({a[i][2], a[idx][2]});
            }
        }
    }

    cout << res.size() << '\n';
    for(auto [x, y] : res) {
        cout << x + 1 << " " << y + 1 << '\n';
    }

    return 0;
}
