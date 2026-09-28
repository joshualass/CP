
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//imp later, do not use an ordered set!

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;


    return 0;
}


// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// #pragma GCC optimize("Ofast,fast-math,unroll-loops,no-stack-protector") 
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,avx,mmx,avx2,fma,tune=native") 

// #include <ext/pb_ds/assoc_container.hpp> //0-indexed
// #include <ext/pb_ds/tree_policy.hpp>
// #include <functional>
// using namespace __gnu_pbds;
// /*
// order_of_key (k) : Number of items strictly smaller than k .
// find_by_order(k) : K-th element in a set (counting from zero).
// */
// template <class T>
// using Tree =
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;

//     vector<pair<Tree<array<int,2>>, Tree<int>>> seqs(1);
    
//     vector<int> a(n);
//     for(int i = 0; i < n; i++) {
//         int x; cin >> x;
//         x--;
//         seqs[0].first.insert({i, x});
//         seqs[0].second.insert(x);
//         a[x] = i;
//     }
    
//     int q; cin >> q;
//     for(int i = 1; i <= q; i++) {
//         seqs.push_back({Tree<array<int,2>>{},Tree<int>{}});
//         int t, s, x; cin >> t >> s >> x;
//         int to = i;
//         int sz = seqs[s].first.size();
//         if(t == 1) {
//             int movecnt = max(0,sz - x);
//             if(movecnt > sz / 2) {
//                 swap(seqs[to], seqs[s]);
//                 swap(s, to);
//                 movecnt = sz - movecnt;
//                 x = 0;
//             }
            
//             for(int j = 0; j < movecnt; j++) {
//                 array<int,2> a = *seqs[s].first.find_by_order(x);
                
//                 seqs[s].first.erase(a);
//                 seqs[s].second.erase(a[1]);
                
//                 seqs[to].first.insert(a);
//                 seqs[to].second.insert(a[1]);
                
//             }
            
//         } else {
//             Tree<int>::iterator it = seqs[s].second.lower_bound(x);
//             int movecnt = sz - (it == seqs[s].second.end() ? sz : seqs[s].second.order_of_key(*it));
//             // cout << "move cnt : " << movecnt << '\n';
//             if(movecnt > sz / 2) {
//                 swap(seqs[to], seqs[s]);
//                 swap(s, to);
//                 movecnt = sz - movecnt;
//                 x = -1;
//             }
            
//             for(int j = 0; j < movecnt; j++) {
//                 int move = *seqs[s].second.lower_bound(x);
//                 int idx = a[move];
                
//                 seqs[s].first.erase({idx, move});
//                 seqs[s].second.erase(move);
                
//                 seqs[to].first.insert({idx, move});
//                 seqs[to].second.insert(move);
                
//             }
//         }
//         cout << seqs[i].first.size() << '\n';
//         // cout << "printing seqs\n";
//         // for(int j = 0; j <= i; j++) {
//         //     cout << "i : " << j << " in seq : ";
//         //     for(array<int,2> x : seqs[j].first) {
//         //         cout << x[1] << " ";
//         //     }
//         //     cout << '\n';
//         // }
//     }

//     return 0;
// }

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// struct Tree {
//     static constexpr T base = 0;
//     vector<map<int,T>> v;
//     int n, size, time;
//     T comb(T a, T b) { //change this when doing maximum vs minimum etc.
//         return a + b;
//     // }
//     Tree(int n = 0, T def = base) {
//         this->n = n; //max number of elements
//         this->time = time;
//         size = 1;
//         while(size < n) size *= 2;
//         v.assign(size * 2, {0, def});
//     }
//     T get(map<int,T> &m, int time) {
//         return (--m.upper_bound(time))->second;
//     }
//     void update(int pos, T val) { //update 0 indexed, assignment
//         assert(pos < n && pos >= 0);
//         int curr = pos + size;
//         time++;
//         v[curr][time] = val;
//         while(curr != 1) {
//             if(curr & 1) { //handles non-communative operations
//                 v[curr / 2][time] = comb(get(v[curr ^ 1], time), get(v[curr], time));
//             } else {
//                 v[curr / 2][time] = comb(get(v[curr], time), get(v[curr ^ 1], time));
//             }
//             curr /= 2;
//         }
//     }
//     // T at(int idx) {
//     //     assert(idx >= 0 && idx < n);
//     //     return v[idx + size];
//     // }
//     int query()
//     T query(int l, int r, ) {//queries in range [l,r)
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

    

//     return 0;
// }
