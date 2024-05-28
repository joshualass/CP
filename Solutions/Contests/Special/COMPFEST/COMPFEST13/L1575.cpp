// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     int n; cin >> n;
//     vector<int> a(n);
//     vector<int> b(n);
//     for(int i = 0; i < n; i++) {
//         int num; cin >> num;
//         num--;
//         if(num <= i) {
//             b[i] = i - num;
//         } else {
//             b[i] = -1;
//         }
//     }

//     cout << "b : " << b << '\n';
//     vector<int> dp(200001, -1);
//     int res = 0;
//     for(int i = 0; i < n; i++) {
//         if(b[i] != -1) {
//             int l = -1, r = n;
//             while(l != r) {
//                 int m = (l + r + 1) / 2;
//                 if(dp[m] == -1 || b[i] < dp[m]) {
//                     r = m - 1;
//                 } else {
//                     l = m;
//                 }
//             }
//             dp[l+1] = b[i];
//             res = max(l+1,res);
//         }
//     }

//     cout << res << '\n';

//     return 0;
// }

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

/*
let a[i] be the value at index i and rem[i] be the number of removals needed to set a[i] = i
observe - a[i] + rem[i] = i
let's solve with sweepline
*/

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
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    set<pair<int,int>> s;
    for(int i = 1; i <= n; i++) {
        int num; cin >> num;
        int removals = i - num;
        if(removals >= 0) s.insert({removals,num});
    }

    Tree<int> tree(n+1);
    for(auto [removals, num] : s) {
        // cout << "r : " << removals << " n : " << num << '\n';
        // cout << "upd val : " << 1 + tree.query(0,num) << '\n';
        tree.update(num, 1 + tree.query(0,num));
    }
    cout << tree.query(0,n+1) << '\n';
    return 0;
}
