#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

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

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x; cin >> n >> x;
    vector<int> a(n);
    for(int &x : a) cin >> x;
    
    int left_size = (n + 1) / 2;
    int right_size = n / 2;
    
    vector<int> left(a.begin(), a.begin() + left_size);
    vector<int> right(a.begin() + left_size, a.end());
    

    //access time is logn
    //O(2^n * n)
    //optimize by using an unordered_map
    pb_map<int,int> dict;
    
    for(int i = 0; i < 1 << left_size; i++) {
        ll sum = 0;
        for(int j = 0; j < left_size; j++) {
            if((i >> j) & 1) {
                sum += left[j];
            }
        }
        dict[sum]++;
    }
    
    ll res = 0;
    
    for(int i = 0; i < 1 << right_size; i++) {
        ll sum = 0;
        for(int j = 0; j < right_size; j++) {
            if((i >> j) & 1) {
                sum += right[j];
            }
        }
        if(x - sum >= 0) res += dict[x - sum];
    }
    
    cout << res << '\n';

    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;
 
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// struct chash {
//     static uint64_t splitmix64(uint64_t x) {
//         // http://xorshift.di.unimi.it/splitmix64.c
//         x += 0x9e3779b97f4a7c15;
//         x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
//         x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
//         return x ^ (x >> 31);
//     }
//     size_t operator()(uint64_t x) const {
//         static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
//         return splitmix64(x + FIXED_RANDOM);
//     }
// };
// template<typename T> using pb_set = gp_hash_table<T, null_type, chash>;  // unordered_set but faster
// template<typename T, typename U> using pb_map = gp_hash_table<T, U, chash>; // unordered_map but faster
 
// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);
    
//     ll n, x; cin >> n >> x;
//     vector<ll> a((n+1) / 2);
//     vector<ll> b(n / 2);
//     for(ll &x : a) cin >> x;
//     for(ll &x : b) cin >> x;
    
//     pb_map<ll,ll> m;
//     for(int bm = 0; bm < 1 << b.size(); bm++) {
//         ll cnt = 0;
//         for(int i = 0; i < b.size(); i++) {
//             if((bm >> i) & 1) {
//                 cnt += b[i];
//             }
//         }
//         m[cnt]++;
//     }
    
//     ll res = 0;
//     for(int bm = 0; bm < 1 << a.size(); bm++) {
//         ll c = 0;
//         for(int i = 0; i < a.size(); i++) {
//             if((bm >> i) & 1) c += a[i];
//         }
//         if(m.find(x-c) != m.end()) {
//             res += m[x-c];
//         }
//     }
//     cout << res << '\n';
//     return 0;
// }



