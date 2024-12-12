#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<string> board(n);
        for (int i = 0; i < n; i++) {
            cin >> board[i];
        }

        for (int d = 0; d < 10; d++) {
            long long max_area = 0;
            vector<pair<int, int>> cells;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (board[i][j] - '0' == d) {
                        cells.push_back({i, j});
                    }
                }
            }

            for (int i = 0; i < cells.size(); i++) {
                for (int j = i + 1; j < cells.size(); j++) {
                    max_area = max(max_area, (long long)abs(cells[i].first - cells[j].first) * abs(cells[i].second - cells[j].second));
                }
            }

            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    int min_r = n, max_r = -1, min_c = n, max_c = -1;
                    for(auto cell : cells){
                        min_r = min(min_r, cell.first);
                        max_r = max(max_r, cell.first);
                        min_c = min(min_c, cell.second);
                        max_c = max(max_c, cell.second);
                    }

                    if (cells.empty()) continue;

                    max_area = max(max_area, (long long)(max_r - min_r) * max(abs(j- min_c), abs(j - max_c)));
                   max_area = max(max_area, (long long)(max_c - min_c) * max(abs(i- min_r), abs(i - max_r)));
                }
            }

            cout << max_area << " ";
        }
        cout << endl;
    }
    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// void solve() {
//     int n; cin >> n;
//     vector<vector<char>> a(n,vector<char>(n));
//     for(int i = 0; i < n; i++) {
//         string s; cin >> s;
//         for(int j = 0; j < n; j++) {
//             a[i][j] = s[j];
//         }
//     }
//     vector<int> res(10);
//     auto rotate = [&]() {
//         vector<vector<char>> b(n,vector<char>(n));
//         for(int i = 0; i < n; i++) {
//             for(int j = 0; j < n; j++) {
//                 b[i][j] = a[j][n-i-1];
//             }
//         }
//         a = b;
//     };
//     auto solve = [&]() {
//         vector<vector<int>> d(n,vector<int>(10));
//         for(int i = 0; i < n; i++) {
//             vector<int> lo(10,-1), hi(10,-1);
//             for(int j = 0; j < n; j++) {
//                 hi[a[i][j] - '0'] = j;
//             }
//             for(int j = n - 1; j >= 0; j--) {
//                 lo[a[i][j] - '0'] = j;
//             }
//             for(int j = 0; j < 10; j++) {
//                 if(lo[j] != -1) {
//                     for(int k = 0; k < i; k++) {
//                         res[j] = max(res[j], (i - k) * d[k][j]);
//                     }
//                     d[i][j] = max(hi[j], n - 1 - lo[j]);
//                 }
//             }
//         }
//     };
//     for(int i = 0; i < 4; i++) {
//         rotate();
//         solve();
//     }
//     for(int i = 0; i < 10; i++) {
//         cout << res[i] << " \n"[i == 9];
//     }
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int casi; cin >> casi;
//     while(casi-->0) solve();

//     return 0;
// }