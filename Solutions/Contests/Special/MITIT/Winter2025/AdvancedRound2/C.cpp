#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

        

    return 0;
}

// #include <bits/stdc++.h>
// typedef long long ll;
// typedef long double ld;
// using namespace std;

// template <typename T, std::size_t N>
// std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
//     os << "[";
//     for (std::size_t i = 0; i < N; ++i) {
//         os << arr[i];
//         if (i < N - 1) {
//             os << ", ";
//         }
//     }
//     os << "]";
//     return os;
// }

// template<typename T>
// std::ostream& operator<<(std::ostream& os, const vector<T> v) {
//     for(auto x : v) os << x << " ";
//     return os;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n; cin >> n;
//     vector<vector<array<ll,2>>> adj(n);
//     for(int i = 1; i < n; i++) {
//         ll u, v, w; cin >> u >> v >> w;
//         u--; v--;
//         adj[u].push_back({v,w});
//         adj[v].push_back({u,w});
//     }

//     vector<ll> p(n), k(n);
//     vector<vector<int>> atlevel;
//     vector<vector<array<ll,2>>> atlevelcosts;

//     auto dfs = [&](auto self, int i, int par, int depth, ll dist) -> void {
//         p[i] = par;
//         k[i] = dist;
//         if(atlevel.size() <= depth) atlevel.push_back({});
//         atlevel[depth].push_back(i);
//         for(auto [c,w] : adj[i]) {
//             if(c != par) {
//                 self(self, c, i, depth + 1, dist + w);
//             }
//         }
//     };

//     dfs(dfs, 0, -1, 0, 0);

//     atlevelcosts.push_back({{0,0}});
//     for(int i = 1; i < atlevel.size(); i++) {
//         atlevelcosts.push_back({});
//         for(int x : atlevel[i]) {
//             ll prevcost;
//             if(i == 1) {
//                 prevcost = 0;
//             } else {
//                 for(int j = 0; j < atlevelcosts[i-1].size(); j++) {
//                     if(atlevelcosts[i-1][j][0] != p[x]) {
//                         prevcost = atlevelcosts[i-1][j][1];
//                         break;
//                     }
//                 }
//             }
//             cout << "x : " << x << " pc : " << prevcost << " k[x] * 2 : " << k[x] * 2 << '\n';
//             atlevelcosts[i].push_back({x, prevcost + k[x] * 2});
//         }
//         sort(atlevelcosts[i].begin(), atlevelcosts[i].end(), [](const auto &lhs, const auto &rhs) {
//             return lhs[1] < rhs[1];
//         });
//     }

//     for(int i = 0; i < atlevelcosts.size(); i++) {
//         cout << "i : " << i << " atc[i] : " << atlevelcosts[i] << '\n';
//     }

//     ll res = LLONG_MAX;
//     for(int i = 0; i < atlevelcosts.back().size(); i++) {
//         res = min(res, atlevelcosts.back()[i][1] - k[atlevelcosts.back()[i][0]]);
//     }

//     cout << res << '\n';

//     return 0;
// }