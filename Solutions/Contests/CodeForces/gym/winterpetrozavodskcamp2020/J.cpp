#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int dfs(int u, int c, vector<int>& color, vector<vector<int>>& adj, int& cnt0, int& cnt1) {
    color[u] = c;
    if (c == 0) {
        cnt0++;
    } else {
        cnt1++;
    }
    for (int v : adj[u]) {
        if (color[v] == -1) {
            if (!dfs(v, 1 - c, color, adj, cnt0, cnt1)) {
                return -1; // Return -1 to signal an odd cycle
            }
        } else if (color[v] == color[u]) {
            return -1; // Return -1 to signal an odd cycle
        }
    }
    return 1; // Return 1 to indicate success
}

int main() {
    // int n, m;
    // cin >> n >> m;
    int n = 300000, m = 300000;

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        // adj[u].push_back(v);
        // adj[v].push_back(u);
        adj[i].push_back((i+1)%n);
        adj[(i+1)%n].push_back(i);
    }

    vector<int> color(n, -1);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            int cnt0 = 0, cnt1 = 0;
            if (dfs(i, 0, color, adj, cnt0, cnt1) == -1) {
                cout << -1 << endl;
                return 0;
            }
            ans += min(cnt0, cnt1);
        }
    }

    cout << ans << endl;

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m; cin >> n >> m;
//     vector<vector<int>> adj(n);
//     for(int i = 0; i < m; i++) {
//         int x, y; cin >> x >> y;
//         x--; y--;
//         adj[x].push_back(y);
//         adj[y].push_back(x);
//     }

//     int res = 0;
//     int ok = 1;
//     vector<int> vis(n,-1);
//     for(int i = 0; i < n; i++) {
//         if(vis[i] == -1 && adj[i].size()) {
//             array<int,2> a{};
//             auto dfs = [&](auto self, int i, int c) -> void {
//                 if(vis[i] != -1) {
//                     if(c != vis[i]) ok = 0;
//                     return;
//                 }
//                 vis[i] = c;
//                 a[c]++;
//                 for(int nei : adj[i]) {
//                     self(self, nei, c ^ 1);
//                 }
//             };
//             dfs(dfs, i, 0);
//             res += min(a[0], a[1]);
//         }
//     }

//     cout << (ok ? res : -1) << '\n';

//     return 0;
// }