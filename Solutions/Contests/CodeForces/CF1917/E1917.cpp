// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll MOD = 1e9 + 7;

// pair<vector<vector<int>>, bool> trydiag1(int n, int k, int diag) {
//     vector<vector<int>> mat(n,vector<int>(n));
//     int left = k - diag * n;
//     if(left % 4 != 0) {
//         return {{{}},0};
//     }
//     for(int i = 0; i < k / n; i++) {
//         for(int j = 0; j < n; j++) {
//             mat[j][(j + i) % n]++;
//         }
//     }
//     for(int i = 0; i < n; i += 2) {
//         for(int j = 0; j < n; j += 2) {
//             if(left == 0) break;
//             if(mat[i][j] == 0 && mat[i+1][j] == 0 && mat[i][j+1] == 0 && mat[i+1][j+1] == 0) {
//                 mat[i][j] = 1;
//                 mat[i][j+1] = 1;
//                 mat[i+1][j] = 1;
//                 mat[i+1][j+1] = 1;
//                 left -= 4;
//             }
//         }
//     }
//     return {mat, (bool) left == 0};
// }

// pair<vector<vector<int>>, bool> trydiag2(int n, int k, int diag) {
//     vector<vector<int>> mat(n, vector<int>(n));
//     int left = k - diag * n;
//     if(left % 4 != 0) {
//         return {{{}},0};
//     }
//     for(int i = 0; i < k / n; i++) {
//         for(int j = 0; j < n; j++) {
//             int idx = -1;
//             if(i < n / 2) {
//                 idx = i * 2;
//             } else {
//                 idx = (i - n / 2) * 2 + 1;
//             }
//             mat[j][(j + idx) % n]++;
//         }
//     }
//     for(int i = 0; i < n - 2; i++) {
//         for(int j = 0; j < n - 2; j++) {
//             if(left == 0) break;
//             if(mat[i][j] == 0 && mat[i+2][j] == 0 && mat[i][j+2] == 0 && mat[i+2][j+2] == 0) {
//                 mat[i][j] = 1;
//                 mat[i+2][j] = 1;
//                 mat[i][j+2] = 1; 
//                 mat[i+2][j+2] = 1;
//                 left -= 4;
//             }
//         }
//     }
//     return {mat, (bool) left == 0};
// }

// pair<vector<vector<int>>, bool> trydiag3(int n, int k, int diag) {
//     vector<vector<int>> mat(n, vector<int>(n));
//     int left = k - diag * n;
//     if(left % 4 != 0) {
//         return {{{}},0};
//     }
//     for(int i = 0; i < k / n; i++) {
//         for(int j = 0; j < n; j++) {
//             if(j == n - 1) {
//                 mat[i][(j + 1) % n]++;
//             } else {
//                 mat[i][j]++;
//             }
//         }
//     }
//     for(int i = 0; i < n-1; i++) {
//         for(int j = 0; j < n-1; j++) {
//             if(left == 0) break;
//             if(mat[i][j] == 0 && mat[i+1][j] == 0 && mat[i][j+1] == 0 && mat[i+1][j+1] == 0) {
//                 mat[i][j] = 1;
//                 mat[i][j+1] = 1;
//                 mat[i+1][j] = 1;
//                 mat[i+1][j+1] = 1;
//                 left -= 4;
//             }
//         }
//     }
//     return {mat, (bool) left == 0};
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
//     for(auto &x : adj) {
//         for(auto &y : x) os << y << " ";
//         os << "\n";
//     }
//     return os;
// }

// void solve() {
//     int n, k; cin >> n >> k;

//     int mostdiags = k / n;
//     pair<vector<vector<int>>, bool> try1 = trydiag1(n, k, 0);
//     pair<vector<vector<int>>, bool> try2 = trydiag1(n, k, min(1,mostdiags));
//     pair<vector<vector<int>>, bool> try3 = trydiag1(n, k, mostdiags);
//     pair<vector<vector<int>>, bool> try4 = trydiag1(n, k, max(0,mostdiags - 1));
//     pair<vector<vector<int>>, bool> try11 = trydiag1(n, k, min(2,mostdiags));
//     pair<vector<vector<int>>, bool> try12 = trydiag1(n, k, min(3,mostdiags));
//     pair<vector<vector<int>>, bool> try13 = trydiag1(n, k, max(0,mostdiags - 2));
//     pair<vector<vector<int>>, bool> try14 = trydiag1(n, k, max(0,mostdiags - 3));

//     pair<vector<vector<int>>, bool> try5 = trydiag2(n, k, 0);
//     pair<vector<vector<int>>, bool> try6 = trydiag2(n, k, min(1,mostdiags));
//     pair<vector<vector<int>>, bool> try7 = trydiag2(n, k, mostdiags);
//     pair<vector<vector<int>>, bool> try8 = trydiag2(n, k, max(0,mostdiags - 1));
//     pair<vector<vector<int>>, bool> try15 = trydiag2(n, k, min(2,mostdiags));
//     pair<vector<vector<int>>, bool> try16 = trydiag2(n, k, min(3,mostdiags));
//     pair<vector<vector<int>>, bool> try17 = trydiag2(n, k, max(0,mostdiags - 2));
//     pair<vector<vector<int>>, bool> try18 = trydiag2(n, k, max(0,mostdiags - 3));

//     // pair<vector<vector<int>>, bool> try21 = trydiag3(n, k, 0);
//     // pair<vector<vector<int>>, bool> try22 = trydiag3(n, k, min(1,mostdiags));
//     // pair<vector<vector<int>>, bool> try23 = trydiag3(n, k, mostdiags);
//     // pair<vector<vector<int>>, bool> try24 = trydiag3(n, k, max(0,mostdiags - 1));
//     // pair<vector<vector<int>>, bool> try25 = trydiag3(n, k, min(2,mostdiags));
//     // pair<vector<vector<int>>, bool> try26 = trydiag3(n, k, min(3,mostdiags));
//     // pair<vector<vector<int>>, bool> try27 = trydiag3(n, k, max(0,mostdiags - 2));
//     // pair<vector<vector<int>>, bool> try28 = trydiag3(n, k, max(0,mostdiags - 3));

//     if(try1.second == 1) {
//         cout << "Yes\n" << try1.first;
//         return;
//     }
//     if(try2.second == 1) {
//         cout << "Yes\n" << try2.first;
//         return;
//     }
//     if(try3.second == 1) {
//         cout << "Yes\n" << try3.first;
//         return;
//     }
//     if(try4.second == 1) {
//         cout << "Yes\n" << try4.first;
//         return;
//     }
//     if(try5.second == 1) {
//         cout << "Yes\n" << try5.first;
//         return;
//     }
//     if(try6.second == 1) {
//         cout << "Yes\n" << try6.first;
//         return;
//     }
//     if(try7.second == 1) {
//         cout << "Yes\n" << try7.first;
//         return;
//     }
//     if(try8.second == 1) {
//         cout << "Yes\n" << try8.first;
//         return;
//     }

//     if(try11.second == 1) {
//         cout << "Yes\n" << try11.first;
//         return;
//     }
//     if(try12.second == 1) {
//         cout << "Yes\n" << try12.first;
//         return;
//     }
//     if(try13.second == 1) {
//         cout << "Yes\n" << try13.first;
//         return;
//     }
//     if(try14.second == 1) {
//         cout << "Yes\n" << try14.first;
//         return;
//     }
//     if(try15.second == 1) {
//         cout << "Yes\n" << try15.first;
//         return;
//     }
//     if(try16.second == 1) {
//         cout << "Yes\n" << try16.first;
//         return;
//     }
//     if(try17.second == 1) {
//         cout << "Yes\n" << try17.first;
//         return;
//     }
//     if(try18.second == 1) {
//         cout << "Yes\n" << try18.first;
//         return;
//     }

//     // if(try21.second == 1) {
//     //     cout << "Yes\n" << try21.first;
//     //     return;
//     // }
//     // if(try22.second == 1) {
//     //     cout << "Yes\n" << try22.first;
//     //     return;
//     // }
//     // if(try23.second == 1) {
//     //     cout << "Yes\n" << try23.first;
//     //     return;
//     // }
//     // if(try24.second == 1) {
//     //     cout << "Yes\n" << try24.first;
//     //     return;
//     // }
//     // if(try25.second == 1) {
//     //     cout << "Yes\n" << try25.first;
//     //     return;
//     // }
//     // if(try26.second == 1) {
//     //     cout << "Yes\n" << try26.first;
//     //     return;
//     // }
//     // if(try27.second == 1) {
//     //     cout << "Yes\n" << try27.first;
//     //     return;
//     // }
//     // if(try28.second == 1) {
//     //     cout << "Yes\n" << try28.first;
//     //     return;
//     // }
//     cout << "No\n";
//     return;
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
const ll MOD = 998244353;

void solve() {
    int n, k; cin >> n >> k;
    if((k & 1) || k == 2 && n != 2 || k == n * n - 2 && n != 2) {
        cout << "No\n";
        return;
    }
    if(k == 2 && n == 2) {
        cout << "Yes\n";
        cout << "1 0\n";
        cout << "0 1\n";
        return;
    }
    // cout << "expr ? " << (k > n * n / 2) << '\n';
    vector<vector<int>> mat(n,vector<int>(n,(k > n * n / 2)));
    // for(vector<int> v : mat) {
    //     for(int i = 0; i < n; i++) {
    //         cout << v[i] << " \n"[i == n - 1];
    //     }
    // }
    if(k > n * n / 2) k = n * n - k;
    if(k & 2) {
        mat[n-1][n-1] ^= 1;
        mat[n-1][n-2] ^= 1;
        mat[n-2][n-1] ^= 1;
        mat[n-2][n-3] ^= 1;
        mat[n-3][n-2] ^= 1;
        mat[n-3][n-3] ^= 1;
        k -= 6;
    }
    for(int i = 0; i < n && k; i += 2) {
        for(int j = 0; j < n && k; j += 2) {
            mat[i][j] ^= 1;
            mat[i+1][j] ^= 1;
            mat[i][j+1] ^= 1;
            mat[i+1][j+1] ^= 1;
            k -= 4;
        }
    }
    cout << "Yes\n";
    for(vector<int> v : mat) {
        for(int i = 0; i < n; i++) {
            cout << v[i] << " \n"[i == n - 1];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}