// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// struct MaxTree {
//     static constexpr T base = {-1,(int)-1e9};
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a[0] > b[0] ? a : b;
//     }
//     MaxTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// template<typename T>
// struct MinTree {
//     static constexpr T base = {-1,(int)1e9};
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a[0] < b[0] ? a : b;
//     }
//     MinTree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, def);
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         v[curr] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2] = comb(v[curr ^ 1], v[curr]);
//             } else {
//                 v[curr / 2] = comb(v[curr], v[curr ^ 1]);
//             }
//             curr /= 2;
//         }
//     }
//     bool isLeaf(int idx) {
//         return idx >= size;
//     }
//     T at(int idx) {
//         assert(idx >= 0 && idx < n);
//         return v[idx + size];
//     }
//     T query(int l, int r) {//queries in range [l,r)
//         return _query(1,0,size,l,r);
//     }
//     T _query(int idx, int currl, int currr, int &targetl, int &targetr) {
//         if(currr <= targetl || currl >= targetr) return base;
//         if(currl >= targetl && currr <= targetr) return v[idx];
//         int mid = (currl + currr) / 2;
//         return comb(
//             _query(idx * 2, currl, mid, targetl, targetr),
//             _query(idx * 2 + 1, mid, currr, targetl, targetr)
//         );
//     }
// };

// void solve() {
//     int n, q; cin >> n >> q;
//     MinTree<array<int,2>> mini(n), mind(n);
//     MaxTree<array<int,2>> maxi(n), maxd(n);
//     for(int i = 0; i < n; i++) {
//         int a; cin >> a;
//         mini.update(i, {a + i, i});
//         maxi.update(i, {a + i, i});
//         mind.update(i, {a - i, i});
//         maxd.update(i, {a - i, i});
//     }
//     auto get_res = [&]() -> int {
//         array<int,2> a = maxd.query(0,n);
//         array<int,2> b = mind.query(0, a[1] + 1);
        
//         return a[0] - b[0];
//     };
//     cout << get_res() << '\n';
//     for(int i = 0; i < q; i++) {
//         int p, x; cin >> p >> x;
//         p--;
//         mini.update(p, {x + p, p});
//         maxi.update(p, {x + p, p});
//         mind.update(p, {x - p, p});
//         maxd.update(p, {x - p, p});
//         cout << get_res() << '\n';
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// const int BS = 448;

// void solve() {
//     int n, q; cin >> n >> q;

//     vector<vector<int>> buckets;
//     vector<array<int,5>> a;
//     int t = n;

//     while(t) {
//         buckets.push_back(vector<int>(min(BS, t)));
//         a.push_back({});
//         t -= min(t,BS);
//     }

//     auto update = [&](int i, int x) -> int {
//         int bucket = i / BS;
//         buckets[bucket][i % BS] = x;
//         int res = 0;
//         int t = INT_MAX;
//         for(int j = 0; j < buckets[bucket].size(); j++) {
//             t = min(t, buckets[bucket][j] - j);
//             res = max(res, buckets[bucket][j] - j - t);
//         }
//         int t = INT_MAX;
//         for(int j = buckets[bucket].size() - 1; j >= 0; j--) {
//             t = min(t, buckets[bucket][j] + j);
//             res = max(res, buckets[bucket][j] + j - t);
//         }
//         a[bucket][0] = res;
//         for(int j = 0; j < buckets[bucket].size(); j++) {

//         }

//     };

// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

template<typename T>
struct SkillCappedSegmentTree {
    static constexpr T base = {(int)-1e9, (int)1e9, (int)-1e9, (int)1e9, (int)-1e9};
    vector<T> v;
    int n, size;
    T comb(T a, T b) { //change this when doing maximum vs minimum etc.
        // return a + b;
        array<int,5> res;
        res[0] = max({a[0], b[0], b[2] - a[1], a[4] - b[3]});
        res[1] = min(a[1], b[1]);
        res[2] = max(a[2], b[2]);
        res[3] = min(a[3], b[3]);
        res[4] = max(a[4], b[4]);
        return res;
    }
    SkillCappedSegmentTree(int n = 0, T def = base) {
        this->n = n; //max number of elements
        size = 1;
        while(size < n) size *= 2;
        v.assign(size * 2, def);
    }
    void update(int pos, int val) { //update 0 indexed, assignment
        assert(pos < n && pos >= 0);
        int curr = pos + size;
        v[curr] = {0, val - pos, val - pos, val + pos, val + pos};
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

void solve() {
    int n, q; cin >> n >> q;
    SkillCappedSegmentTree<array<int,5>> ffTree(n);
    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ffTree.update(i, x);
    }
    cout << ffTree.query(0,n)[0] << '\n';
    for(int i = 0; i < q; i++) {
        int p, x; cin >> p >> x;
        ffTree.update(p - 1, x);
        cout << ffTree.query(0,n)[0] << '\n';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}