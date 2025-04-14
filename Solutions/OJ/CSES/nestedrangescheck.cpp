#pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<T> v;
//     int n, size;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
struct chash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster

struct FT {
    vector<int> s;
    FT(int n) : s(n) {}
    void update(int pos, int dif) { //a[pos] += dif
        for(; pos < s.size(); pos |= pos + 1) s[pos] += dif;
    }
    int query(int pos) {
        int res = 0;
        for(; pos > 0; pos &= pos - 1) res += s[pos-1];
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >> n;
    vector<pair<int,int>> ranges(n);
    vector<pair<int,int>> uranges;
    vector<int> compress_coords;
    unordered_map<int,int> ids;
    for(int i = 0; i < n; i++) {
        int a, b; cin >> a >> b; 
        ranges[i] = {a,b};
        compress_coords.push_back(a);
        compress_coords.push_back(b);
    }
    int i = 0;
    sort(compress_coords.begin(), compress_coords.end());
    compress_coords.erase(unique(compress_coords.begin(), compress_coords.end()),compress_coords.end());
    for(int x : compress_coords) {
        ids[x] = i++;
    }

    FT treec(compress_coords.size());
    FT treew(compress_coords.size());
    for(pair<int,int> p : ranges) {
        p = {ids[p.first], ids[p.second]};
        uranges.push_back({p.first, p.second});
        treec.update(p.second, 1); //insert right endpoints
    }

    sort(uranges.begin(), uranges.end());

    pb_map<ll, int> resc;
    pb_map<ll, int> resw;
    vector<pair<int,int>>::iterator rit = uranges.begin();
    vector<pair<int,int>>::iterator wit = uranges.begin();
    for(auto p : uranges) {
        while(rit != uranges.end() && (*rit).first < p.first) {
            treec.update((*rit).second, -1);
            rit++;
        }
        while(wit != uranges.end() && (*wit).first <= p.first) {
            treew.update((*wit).second, 1);
            wit++;
        }
        // resc[p] = treec.query(p.first, p.second + 1);
        resc[1000000001LL * p.first + p.second] = treec.query(p.second + 1) - treec.query(p.first);
        // resw[p] = treew.query(p.second, compress_coords.size());
        resw[1000000001LL * p.first + p.second] = treew.query(compress_coords.size()) - treew.query(p.second);
    }

    for(int i = 0; i < n; i++) {
        pair<int,int> p = {ids[ranges[i].first], ids[ranges[i].second]};
        cout << ((bool) resc[1000000001LL * p.first + p.second] - 1)  << " \n"[i == n - 1];
    }

    for(int i = 0; i < n; i++) {
        pair<int,int> p = {ids[ranges[i].first], ids[ranges[i].second]};
        cout << ((bool) resw[1000000001LL * p.first + p.second] - 1) << " \n"[i == n - 1];
    }

    return 0;
}