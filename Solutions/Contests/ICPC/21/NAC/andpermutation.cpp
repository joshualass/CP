#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    

    return 0;
}


// #include <bits/stdc++.h>
// using namespace std;
// typedef long long ll;
// typedef long double ld;
// typedef pair<int, int> pii;
// typedef pair<ll, ll> pll;
// typedef vector<int> vi;
// typedef vector<ll> vl; 
// typedef vector<bool> vb;
// typedef vector<ld> vd;
// typedef vector<vector<int>> vvi;
// typedef vector<vector<ll>> vvl;
// typedef vector<vector<bool>> vvb;
// typedef vector<vector<ld>> vvd;
// // typedef __int128 lll;
// // typedef __float128 lld;

// struct Trie {
//     struct TrieNode {
//         TrieNode* c[2];
//         int numWords = 0;   //counts how many words use this node as prefix
//     };

//     TrieNode head;

//     Trie() {
//         this->head = TrieNode();
//     }

//     void insert(ll val){
//         TrieNode* ptr = &head;
//         for(int i = 0; i < 60; i++) {
//             ptr->numWords ++;
//             int ind = val % 2;
//             val /= 2;
//             if(ptr->c[ind] == nullptr) {
//                 ptr->c[ind] = new TrieNode();
//             }
//             ptr = ptr->c[ind];
//         }
//         ptr->numWords ++;
//     }

//     void remove(ll val) {
//         TrieNode* ptr = &head;
//         for(int i = 0; i < 60; i++) {
//             ptr->numWords --;
//             int ind = val % 2;
//             val /= 2;
//             ptr = ptr->c[ind];
//         }
//         ptr->numWords --;
//     }

//     bool is_in(ll val) {
//         TrieNode* ptr = &head;
//         for(int i = 0; i < 60; i++) {
//             if(ptr->numWords == 0) return false;
//             int ind = val % 2;
//             val /= 2;
//             if(ptr->c[ind] == nullptr) return false;
//             ptr = ptr->c[ind];
//         }
//         if(ptr->numWords == 0) return false;
//         return true;
//     }

//     ll get_max(ll val) {
//         ll ans = 0;
//         TrieNode* ptr = &head;
//         for(int i = 0; i < 60; i++) {
//             int ind = val % 2;
//             val /= 2;
//             if(ind == 0) {
//                 //can be 0 or 1
//                 if(ptr->c[1] != nullptr && ptr->c[1]->numWords != 0) {
//                     ans += ((ll) 1 << (ll) i);
//                     ptr = ptr->c[1];
//                 }
//                 else {
//                     ptr = ptr->c[0];
//                 }
//             }
//             else {
//                 //has to be 0
//                 ptr = ptr->c[0];
//             }
//         }
//         return ans;
//     }
// };

// void gentc() {
//     // vi seed = {16, 29, 38};
//     vi seed = {3, 6, 5};
//     vi a(0);
//     for(int i = 0; i < (1 << 10); i++){
//         bool is_valid = false;
//         for(int x : seed) if((i & x) == i) is_valid = true;
//         if(is_valid) a.push_back(i);
//     }
//     cout << a.size() << "\n";
//     for(int x : a) cout << x << " ";
//     cout << endl;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL); cout.tie(NULL);
    
//     gentc();

//     int n;
//     cin >> n;
//     vl a(n);
//     for(int i = 0; i < n; i++) cin >> a[i];
//     while(true){
//         //generate superset
//         ll sset = 0;
//         for(ll x : a) sset |= x;
//         cout << "SSET : " << sset << "\n";
//         //remove real-real matches
//         set<ll> s;
//         for(ll x : a) s.insert(x);
//         vl na;
//         for(ll x : a) {
//             if(!s.count(sset ^ x)) na.push_back(x);
//             else {
//                 if(x >= (sset ^ x)) cout << "MATCH : " << x << " " << (sset ^ x) << "\n";
//             }
//         }
//         if(na.size() == a.size()) break;
//         a = na;
//     }
//     for(ll x : a) cout << x << " ";
//     cout << "\n";


//     // Trie t;
//     // for(int i = 0; i < n; i++){
//     //     t.insert(a[i]);
//     // }
//     // vector<pll> b(n);
//     // for(int i = 0; i < n; i++){
//     //     b[i] = {a[i], i};
//     // }
//     // sort(b.begin(), b.end(), [](pll a, pll b) -> bool {
//     //     return __builtin_popcountll(a.first) > __builtin_popcountll(b.first);
//     // });
//     // map<ll, int> indmp;
//     // for(int i = 0; i < n; i++) indmp[b[i].first] = b[i].second;
//     // vl ans(n);
//     // for(int i = 0; i < n; i++){
//     //     if(!t.is_in(a[i])) continue;
//     //     t.remove(a[i]);
//     //     ll match = t.get_max(a[i]);
//     //     t.remove(match);
//     //     ans[indmp[a[i]]] = match;
//     //     ans[indmp[match]] = a[i];
//     // }
//     // for(int i = 0; i < n; i++) cout << ans[i] << " ";
//     // cout << "\n";

//     // {
//     //     cout << "CHECK VALID\n";
//     //     for(int i = 0; i < n; i++) cout << (ans[i] & a[i]) << " ";
//     //     cout << "\n";
//     // }
    
//     return 0;
// }
