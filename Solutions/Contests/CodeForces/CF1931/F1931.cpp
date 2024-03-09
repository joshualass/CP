// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 998244353;

// void solve(bool b) {
//     int n, k; cin >> k >> n;
//     bool ok;
//     vector<vector<int>> sequences(n,vector<int>(k));
//     for(auto &x : sequences) for(auto &y: x) cin >> y;
//     if(b) {
//         // cout << "n:" << n << "k:" << k << "goon";
//         // for(auto &x : sequences) for(auto &y : x) cout << y;
//         // cout << '\n';
//     }
//     if(k > 4) {
//         ok = 1;
//         for(int i = 0; i < min(n,3); i++) {
//             for(int j = 0; j < n; j++) {
//                 if(i != j) {
//                     int lo_idx = 1;
//                     for(int l = 1; l < k; l++) {
//                         if(sequences[i][l] == sequences[j][0]) continue;
//                         if(sequences[j][lo_idx] == sequences[i][0]) lo_idx++;
//                         if(sequences[i][l] != sequences[j][lo_idx++]) {
//                             ok = 0;
//                             // cout << "i : " << i << " j : " << j << " l : " << l << " lo_idx : " << lo_idx << '\n';    
//                         }
//                     }
//                     // if(lo_idx != k) ok = 0;
//                 }
//             }
//         }
//     } else {
//         ok = 0;
//         vector<int> perm(k);
//         iota(perm.begin(), perm.end(), 1);
//         if(k == 1) {
//             ok = 1;
//         } else {
//             while(1) {
//                 bool found = 1;
//                 for(int i = 0; i < n; i++) {
//                     int lo = 1;
//                     // for(int j = 0; j < k; j++) {
//                     //     if(perm[j] != sequences[i][lo]) continue;
//                     //     lo++;
//                     //     if(lo == k) break;
//                     // }
//                     for(int j = 0; j < k; j++) {
//                         if(perm[j] == sequences[i][0]) continue;
//                         if(perm[j] == sequences[i][lo]) lo++;
//                     }
//                     found &= lo == k;
//                 }
//                 ok |= found;
//                 if(next_permutation(perm.begin(), perm.end()) == 0) {
//                     break;
//                 }
//             }
//         }
//     }

//     cout << (ok ? "YES" : "NO") << '\n';
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     for(int i = 0; i < casi; i++) {
//         if(i == 472) {
//             solve(1);
//         } else {
//             solve(0);
//         }
//     }
//     // while(casi-->0) solve();

//     return 0;
// }
#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;



template<typename T>
std::ostream& operator<<(std::ostream& os, const vector<T> v) {
    for(auto &x : v) os << x << " ";
    return os;
}

void solve() {
    int n, k; cin >> n >> k;
    vector<set<int>> v(n);
    for(int i = 0; i < k; i++) {
        int prev; cin >> prev;
        prev--;
        for(int j = 1; j < n; j++) {
            int next; cin >> next;
            next--;
            if(j != 1) {
                v[prev].insert(next);
            }
            prev = next;
        }
    }
    vector<int> indegrees(n);
    for(int i = 0; i < n; i++) {
        for(auto x : v[i]) {
            indegrees[x]++;
        }
    }
    queue<int> q;
    for(int i = 0; i < n; i++) {
        if(indegrees[i] == 0) {
            q.push(i);
        }
    }
    while(q.size()) {
        int i = q.front();
        q.pop();
        for(int x : v[i]) {
            indegrees[x]--;
            if(indegrees[x] == 0) {
                q.push(x);
            }
        }
    }
    // cout << "indegrees : " << indegrees << '\n';
    cout << (count(indegrees.begin(), indegrees.end(), 0) == n ? "YES" : "NO") << '\n';
    
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}