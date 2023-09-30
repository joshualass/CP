#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

// void solve() { //did not read the non-overlapping part :)
//     int n; cin >> n;
//     vector<int> v(n);
//     for(auto &x: v) cin >> x;
//     vector<bool> poss(8193,false);
//     poss[0] = true;
//     for(int i = 1; i <= n; i++) {
//         unordered_set<int> s;
//         for(int j = 0; j < n; j++) {
//             if(v[j] == i) {
//                 s.clear();
//             } else if(v[j] < i && s.find(v[j]) == s.end()) {
//                 s.insert(v[j]);
//             }
//             if(s.size() == i) {
//                 poss[i] = true;
//             }
//         }

//     }
//     int most = 0;
//     for(int i = 0; i < poss.size(); i++) {
//         for(int j = 0; j < poss.size(); j++) {
//             if(poss[i] && poss[j]) {
//                 poss[i^j] = true;
//                 most = max(most,i^j);
//             }
//         }
//     }
//     cout << most << "\n";
// }

// void solve() {
//     int n; cin >> n;
//     vector<int> v(n);
//     for(auto &x: v) cin >> x;
//     vector<vector<bool>> reachable(n,vector<bool>(5001));
//     for(int i = 0; i < n; i++) {
//         vector<bool> found(5001);
//         int mex = 0;
//         if(i != 0) {
//             reachable[i] = reachable[i-1];
//             // for(int j = 0; j <= 5000; j++) {
//             //     reachable[i][j] = reachable[i-1][j] | reachable[i][j];
//             // }
//         }
//         for(int j = i; j >= 0; j--) {
//             found[v[j]] = true;
//             while(mex <= 5000 && found[mex]) {
//                 mex++;
//             }
//             if(j != 0 && !reachable[j][mex]) {
//                 for(int k = 0; k <= 5000; k++) {
//                     if(reachable[j-1][k]) {
//                         reachable[i][k ^ mex] = true;
//                     }
//                 }
//             }
//             reachable[i][mex] = true;
//         }
//     }
//     // for(int i = 0; i < 5; i++) {
//     //     for(int j = 0; j < 5; j++) {
//     //         cout << reachable[i][j] << " ";
//     //     }
//     //     cout << "\n";
//     // }
//     for(int i = 5000; i >= 0; i--) {
//         if(reachable[n-1][i]) {
//             cout << i << "\n";
//             return;
//         }
//     }
//     cout << "ending?";
// }

void solve() {
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}