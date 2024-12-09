#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

long long ways_to_complete_iterative(const vector<int>& b, int n, int m) {
    vector<vector<long long>> dp(n + m + 2, vector<long long>(n + m + 1, 0));
    dp[2][0] = 1;  // Initial state: no brackets placed
    const long long INF = 1e18; // Infinity value to prevent overflow


    for (int i = 2; i <= n + m; ++i) {
        for (int j = 0; j <= n + m; ++j) {
            if (b[i] == -1) {
                if (j + 1 <= n + m) dp[i + 1][j + 1] = min(INF, dp[i+1][j+1] + dp[i][j]);
                if (j - 1 >= 0) dp[i + 1][j - 1] = min(INF, dp[i+1][j-1] + dp[i][j]);
            } else {
                int next_balance = j + (b[i] == 0 ? 1 : -1);
                if (next_balance >= 0 && next_balance <= n + m) {
                    dp[i + 1][next_balance] = min(INF, dp[i + 1][next_balance] +  dp[i][j]);
                }
            }
        }
    }
    return dp[n + m + 1][0];
}

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;

    vector<vector<int>> priority(n, vector<int>(m));
    vector<tuple<int, int, int>> cells_by_priority;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> priority[i][j];
            cells_by_priority.emplace_back(priority[i][j], i, j);
        }
    }
    sort(cells_by_priority.begin(), cells_by_priority.end());

    vector<vector<char>> result(n, vector<char>(m));
    vector<int> b(n + m + 2, -1);

    for (const auto& cell_info : cells_by_priority) {
        int p, row, col;
        tie(p, row, col) = cell_info;
        int d = row + col + 2;

        if (b[d] != -1) continue;

        vector<int> b_copy_open = b;
        b_copy_open[d] = 0;
        long long open_ways = ways_to_complete_iterative(b_copy_open, n, m);
        // cout << "d : " << d << " open_ways : " << open_ways << '\n';

        if (k <= open_ways) {
            b[d] = 0;
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (r + c + 2 == d) result[r][c] = '(';
                }
            }
        } else {
            k -= open_ways;
            b[d] = 1;
            for (int r = 0; r < n; ++r) {
                for (int c = 0; c < m; ++c) {
                    if (r + c + 2 == d) result[r][c] = ')';
                }
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << result[i][j];
        }
        cout << endl;
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;
// const ll inf = 1e18;

// // template<typename T>
// // std::ostream& operator<<(std::ostream& os, const vector<vector<T>> adj) {
// //     for(auto x : adj) {
// //         for(auto y : x) os << y << " ";
// //         os << "\n";
// //     }
// //     return os;
// // }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// // ll cntpos(vector<int> b) {
// //     vector<ll> dp(b.size());
// //     dp[0] = 1;
// //     for(int i = 0; i < b.size(); i++) {
// //         vector<ll> next(b.size());
// //         for(int j = 0; j < b.size(); j++) {
// //             if((b[i] == -1 || b[i] == 0) && j != b.size() - 1) {
// //                 next[j+1] += dp[j];
// //             }
// //             if((b[i] == -1 || b[i] == 1) && j) {
// //                 next[j-1] += dp[j];
// //             }
// //         }
// //         dp = next;
// //         for(int j = 0; j < b.size(); j++) {
// //             dp[j] = min(dp[j],inf);
// //         }
// //     }
// //     // cout << "b : " << b << " dp[0] : " << dp[0] << '\n';
// //     return dp[0];
// // }

// long long ways_to_complete_iterative(const vector<int>& b, int n, int m) {
//     vector<vector<long long>> dp(n + m + 2, vector<long long>(n + m + 1, 0));
//     dp[2][0] = 1;  // Base case: diagonal 2 (1,1) starts with balance 1

//     // cout << "b : " << b << '\n';

//     for (int i = 2; i <= n + m; ++i) {
//         for (int j = 0; j <= n + m; ++j) {
//             if (b[i] == -1) { // Diagonal not yet assigned
//                 if (j + 1 <= n + m) dp[i + 1][j + 1] += dp[i][j];
//                 if (j - 1 >= 0) dp[i + 1][j - 1] += dp[i][j];
//             } else { // Diagonal already assigned
//                 int next_balance = j + (b[i] == 0 ? 1 : -1);
//                 if (next_balance >= 0 && next_balance <= n + m) {
//                     dp[i + 1][next_balance] += dp[i][j];
//                 }
//             }
//             // cout << "i : " << i << " j : " << j << " dp[i][j] : " << dp[i][j] << '\n';
//         }
//     }
//     // cout << "dp : " << dp << '\n';
//     return dp[n + m + 1][0]; // Number of ways ending with balance 0
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     ll n, m, k; cin >> n >> m >> k;
//     vector<array<int,2>> a(n+m-1,{INT_MAX,-1});
//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             int x; cin >> x;
//             a[i+j][0] = min(a[i+j][0],x);
//             a[i+j][1] = i + j;
//         }
//     }

//     sort(a.begin(),a.end());
//     vector<int> b(n+m+2,-1);

//     for(int i = 0; i < n + m - 1; i++) {
//         b[a[i][1]+2] = 0;
        
//         ll c = ways_to_complete_iterative(b, n, m);
//         cout << "b : " << b << " c : " << c << '\n';
//         if(k > c) {
//             b[a[i][1]+2] = 1;
//             k -= c;
//         }
//     }

//     for(int i = 0; i < n; i++) {
//         for(int j = 0; j < m; j++) {
//             cout << (b[i+j+2] ? ')' : '(');
//         }
//         cout << '\n';
//     }

//     return 0;
// }