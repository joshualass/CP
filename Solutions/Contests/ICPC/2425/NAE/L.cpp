#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T> 
struct Tree {
    static constexpr T base = 0;
    vector<T> v;
    int n, size;
    T comb(T a, T b) {
        return a + b;
    }
    Tree(int n = 0, T def = base) {
        this->n = n;
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, T val) {
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = val;
        while(curr != 1) {
            if(curr & 1) {
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
    T query(int l, int r) {
        return _query(1, 0, size, l, r);
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
    vector<vector<int>> ranges(n);
    vector<vector<int>> nums(2*n);
    vector<int> a(n * 2);
    for(int i = 0; i < n * 2; i++) {
        int c, d; cin >> c >> d;
        c--; d--;
        ranges[c].push_back(i);
        nums[d].push_back(i);
        a[i] = d;
    }

    ll res = 0;

    vector<vector<int>> queries(n * 2);
    for(int i = 0; i < n; i++) {
        ranges[i][1]++;
        queries[ranges[i][0]].push_back(ranges[i][1]);
        res += ranges[i][1] - ranges[i][0];
    }

    Tree<int> tree(n * 2);
    for(int i = 0; i < n * 2; i++) {
        reverse(nums[i].begin(), nums[i].end());
        if(nums[i].size()) {
            // cout << "nums[i].back() : " << nums[i].back() << '\n';
            tree.update(nums[i].back(), 1);
            nums[i].pop_back();
        }
    }

    for(int i = 0; i < n * 2; i++) {
        if(i) {
            if(nums[a[i-1]].size()) {
                tree.update(nums[a[i-1]].back(), 1);
                nums[a[i-1]].pop_back();
            }
        }
        for(int r : queries[i]) {
            res -= tree.query(i,r);
        }
    }

    cout << res << '\n';

    return 0;
}