// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// /*
// soon to be candidate master dmot's idea

// let dp[i] be the maximum f(S) from using elements up to i
// to calculate dp[i], we will take the maximum of
// 1. dp[i-1]
// 2. let i be y, find the smallest x such that the segment is satisfied and take calculate y - x + 1 + dp[x - 1]

// modified to take the sequence where we get the closest value >= 0

// */

// template <typename T, typename D>
// std::ostream& operator<<(std::ostream& os, const pair<T,D> &p) {
//     os << '(' << p.first << ", " << p.second << ") ";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     // for(auto &x : v) os << x << " ";
//     // return os;
//     for(int i = 1; v.size() >= 1 << i; i++) {
//         for(int j = 1 << (i - 1); 1 << i > j; j++) {
//             // os << "i : " << i << " j : " << j << ' ';
//             os << v[j] << ' ';
//         }
//         os << '\n';
//     }
//     return os;
// }

// template<typename T>
// struct Tree {
//     static constexpr T base = {INT_MAX,-1};
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         if(a.first < b.first) {
//             return a;
//         } else {
//             if(a.first == b.first) {
//                 if(a.second > b.second) {
//                     return b;
//                 } else {
//                     return a;
//                 }
//             } else {
//                 return b;
//             }
//         }
//     }
//     Tree(int n = 0, T def = base) {
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
//             if(curr & 1) { //non
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

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll n; cin >> n;
//     vector<ll> a(n);
//     for(ll &x : a) cin >> x;

//     vector<pair<ll,ll>> suf(n);
//     vector<pair<ll,ll>> vals(n);
//     for(int i = n - 1; i >= 0; i--) {
//         if(i != n - 1) {
//             suf[i].first += suf[i+1].first;
//             vals[i].first = suf[i+1].first;
//         } 
//         suf[i].first += a[i];
//         vals[i].second = i;
//         suf[i].second = i;
//     }

//     // cout << "suf : " << suf << '\n';
//     // cout << "vals : " << vals << '\n';

//     vector<ll> idxs(n);
//     Tree<pair<ll,int>> tree(n);

//     sort(suf.rbegin(), suf.rend());
//     sort(vals.rbegin(), vals.rend());

//     int lo = 0;
//     for(int i = 0; i < n; i++) {
//         while(lo != n && suf[lo].first >= vals[i].first) {
//             tree.update(suf[lo].second, suf[lo]);
//             lo++;
//         }
//         // cout << "vals[i] : " << vals[i] << '\n';
//         // cout << "tree : \n" << tree.v << '\n';
//         pair<int,ll> qval = tree.query(0, vals[i].second + 1);
//         // cout << "qval : " << qval << '\n';
//         idxs[vals[i].second] = qval.second;
//     }

//     // cout << "idxs : " << idxs << '\n';
//     // cout << "idxs :";
//     // for(auto x : idxs) {
//     //     cout << " " << x;
//     // }
//     // cout << '\n';

//     vector<ll> dp(n);
    
//     for(int i = 0; i < n; i++) {
//         if(i != 0) {
//             dp[i] = dp[i-1];
//         }
//         ll idx = idxs[i];
//         if(idx != -1) {
//             dp[i] = max(dp[i], (idx == 0 ? 0 : dp[idx-1]) + i - idx + 1);
//         }
//     }
//     cout << dp.back() << '\n';

//     return 0;
// }

//tutorial learning time :)

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
struct Tree {
    static constexpr T base = -1e9;
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
    
    ll n; cin >> n;
    vector<ll> a(n);
    for(ll &x : a) cin >> x;

    //prefs store prefix sum, index
    vector<pair<ll,ll>> prefs(n);

    for(int i = 0; i < n; i++) {
        if(i != 0) {
            prefs[i].first += prefs[i-1].first;
        }
        prefs[i].first += a[i];
        prefs[i].second = i;
    }

    sort(prefs.begin(), prefs.end());
    //idxs store for index i, which index it is in prefs
    vector<int> idxs(n);
    for(int i = 0; i < n; i++) {
        idxs[prefs[i].second] = i;
    }

    Tree<int> tree(n);
    vector<int> dp(n);

    for(int i = 0; i < n; i++) {
        if(i != 0) {
            dp[i] = dp[i-1];
        }
        if(prefs[idxs[i]].first >= 0) {
            dp[i] = i + 1;
        }
        int v = tree.query(0,idxs[i]);
        dp[i] = max(dp[i], i + 1 + v);
        tree.update(idxs[i], dp[i] - (i + 1));
    }
    // cout << "dp : " << dp << '\n';
    cout << dp.back() << '\n';

    return 0;
}