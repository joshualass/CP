#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> next(n + 1);
    for (int i = 1; i <= n; ++i) {
        next[i] = a[i];
    }

    int val = 0;
    int pos = x;
    while (pos != 0) {
        val++;
        pos = next[pos];
    }

    vector<int> lengths;
    vector<bool> pointed_to(n + 1, false);
    for (int i = 1; i <= n; ++i) {
        if (next[i] != 0) {
            pointed_to[next[i]] = true;
        }
    }

    vector<int> starts;
    for (int i = 1; i <= n; ++i) {
        if (!pointed_to[i]) {
            starts.push_back(i);
        }
    }

    for (int start : starts) {
        int len = 0;
        int curr = start;
        bool in_x_chain = false;

        while (curr != 0) {
            if (curr == x) {
                in_x_chain = true;
            }
            len++;
            curr = next[curr];
        }
        if (!in_x_chain) {
            lengths.push_back(len);
        }
    }

    vector<bool> dp(n + 1, false);
    dp[0] = true;

    for (int len : lengths) {
        for (int i = n; i >= len; --i) {
            if (dp[i - len]) {
                dp[i] = true;
            }
        }
    }

    vector<int> ans;
    for (int i = 0; i <= n; ++i) {
        if (dp[i]) {
            ans.push_back(i + val);
        }
    }

    sort(ans.begin(), ans.end());
    for (int pos : ans) {
        cout << pos << endl;
    }

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, x; cin >> n >> x;
//     vector<vector<int>> adj(n);
//     vector<int> b(n);
//     x--;
//     for(int i = 0; i < n; i++) {
//         int y; cin >> y;
//         y--;
//         if(y >= 0) {
//             adj[i].push_back(y);
//             adj[y].push_back(i);
//         }
//         b[i] = y;
//     }

//     // for(int i = 0; i < n; i++) {
//     //     cout << "i : " << i << " adj[i] : " << adj[i] << '\n';
//     // }

//     vector<int> a;
//     vector<int> vis(n);
//     for(int i = 0; i < n; i++) {
//         if(vis[i] == 0) {
//             int sz = 0, containsx = 0;
//             auto dfs = [&](auto self, int j) -> void {
//                 if(vis[j]) return;
//                 if(j == x) containsx = 1;
//                 sz++;
//                 vis[j] = 1;
//                 for(int c : adj[j]) {
//                     self(self, c);
//                 }
//             };
//             dfs(dfs, i);
//             // cout << "i : " << i << " sz : " << sz << " cx : " << containsx << '\n';
//             if(!containsx) {
//                 a.push_back(sz);
//             }
//         }
//     }

//     int cntsmall = 0;
//     while(b[x] != -1) {
//         cntsmall++;
//         x = b[x];
//     }


//     vector<int> dp(n+1);
//     dp[0] = 1;
//     // cout << "a : " << a << '\n';

//     for(int x : a) {
//         for(int i = n - 1; i >= 0; i--) {
//             if(x + i <= n) {
//                 dp[x+i] |= dp[i];
//             }
//         }
//     }

//     // cout << "dp : " << dp << '\n';

//     for(int i = 0; i < n; i++) {
//         if(dp[i]) {
//             cout << i + 1 + cntsmall << '\n';
//         }
//     }

//     return 0;
// }