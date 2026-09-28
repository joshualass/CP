#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

template<typename T>
struct Tree {
    static constexpr T base = 0;
    vector<vector<pair<T,pair<int,int>>>> v; // {i, {val,{c1,c2}}}
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        return a + b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, {{base,{0,0}}});
    }
    void update(int pos, T val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr].push_back({val,{0,0}});
        while(curr != 1) {
            if(curr & 1) { //non-communative
                v[curr / 2].push_back({
                    comb(v[curr ^ 1].back().first, v[curr].back().first),
                    {v[curr ^ 1].size() - 1, v[curr].size() - 1}
                });
            } else {
                v[curr / 2].push_back({
                    comb(v[curr].back().first, v[curr ^ 1].back().first),
                    {v[curr].size() - 1, v[curr ^ 1].size() - 1}
                });
            }
            curr /= 2;
        }
    }
    bool isLeaf(int idx) {
        return idx >= size;
    }
    vector<pair<T,pair<int,int>>> at(int idx) {
        assert(idx >= 0 && idx < n);
        return v[idx + size];
    }
    T query(int l, int r, int time) {//queries in range [l,r)
        return _query(1,0,size,l,r,time);
    }
    T _query(int idx, int currl, int currr, int &targetl, int &targetr, int time) {
        if(currr <= targetl || currl >= targetr) return base;
        if(currl >= targetl && currr <= targetr) {
            return v[idx][time].first;
        }
        int mid = (currl + currr) / 2;
        return comb(
            _query(idx * 2, currl, mid, targetl, targetr, v[idx][time].second.first),
            _query(idx * 2 + 1, mid, currr, targetl, targetr, v[idx][time].second.second)
        );
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i].first;
        v[i].second = i;
    }
    sort(v.begin(), v.end());

    Tree<ll> tree(n);

    for(int i = 0; i < n; i++) {
        tree.update(v[i].second, v[i].first);
    }

    ll ans = 0;
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        ll l, r, x; cin >> l >> r >> x;
        l ^= ans;
        r ^= ans; 
        x ^= ans;

        int lo = -1, hi = n - 1;
        while(lo != hi) {
            int m = (lo + hi + 1) / 2;
            if(v[m].first <= x) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }
        ans = tree.query(l-1,r,lo + 1);
        cout << ans << '\n';
    }

    return 0;
}