#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <array>

using namespace std;

vector<int> adj[200005];
bool is_hometown[200005];
int subtree_size[200005];
int n, k;
int center_city = -1;

void dfs(int u, int p, int root) {
    subtree_size[u] = is_hometown[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, root);
            subtree_size[u] += subtree_size[v];
        }
    }

    if (center_city == -1) {
        bool ok = true;
        for (int v : adj[u]) {
            if (v != p && subtree_size[v] > k) {
                ok = false;
                break;
            }
        }
        if (ok && (2 * k - subtree_size[u]) <= k) {
            center_city = u;
        }
    }
}

int main() {
    cin >> n >> k;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> hometowns(2 * k);
    for (int i = 0; i < 2 * k; ++i) {
        cin >> hometowns[i];
        is_hometown[hometowns[i]] = true;
    }

    dfs(hometowns[0], -1, 0);

    cout << 1 << endl;
    cout << center_city << endl;

    vector<array<int,2>> pairings;

    priority_queue<array<int,2>> pq;

    vector<vector<int>> a;
    auto dfs2 = [&](auto self, int i, int p) -> void {
        if(is_hometown[i]) a.back().push_back(i);
        for(int c : adj[i]) {
            if(c != p) {
                self(self, c, i);
            }
        }
    };

    for(int c : adj[center_city]) {
        a.push_back({});
        dfs2(dfs2, c, center_city);
        if(a.back().size()) {
            pq.push(array<int,2>{(int)a.back().size(), (int)a.size() - 1});
        }
    }

    if(is_hometown[center_city]) {
        pq.push({1,(int)a.size()});    
        a.push_back({center_city});
    }

    while(pq.size()) {
        array<int,2> b = pq.top();
        pq.pop();
        array<int,2> c = pq.top();
        pq.pop();
        pairings.push_back({a[b[1]].back(), a[c[1]].back()});
        a[b[1]].pop_back();
        a[c[1]].pop_back();
        if(a[b[1]].size()) {
            pq.push({(int)a[b[1]].size(), b[1]});
        }
        if(a[c[1]].size()) {
            pq.push({(int)a[c[1]].size(), c[1]});
        }
    }

    for (int i = 0; i < k; ++i) {
        cout << pairings[i][0] << " " << pairings[i][1] << " " << center_city << endl;
    }

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

//     int n, k; cin >> n >> k;
//     vector<vector<int>> adj(n);
//     for(int i = 1; i < n; i++) {
//         int a, b; cin >> a >> b;
//         a--; b--;
//         adj[a].push_back(b);
//         adj[b].push_back(a);
//     }

//     vector<int> cit(n);
//     for(int i = 0; i < k * 2; i++) {
//         int x; cin >> x;
//         cit[x-1] = 1;
//     }

//     int s = -1;
//     auto dfs1 = [&](auto self, int i, int p) -> int {
//         int cb = 0, mb = 0;
//         for(int c : adj[i]) {
//             if(c != p) {
//                 int r = self(self, c, i);
//                 cb += r;
//                 mb = max(mb, r);
//             }
//         }
//         if(max(mb, k * 2 - cb) <= k) s = i;
//         return cb + cit[i];
//     };

//     dfs1(dfs1, 0, -1);

//     // cout << "s : " << s << endl;

//     priority_queue<array<int,2>> pq;

//     vector<vector<int>> a;
//     auto dfs2 = [&](auto self, int i, int p) -> void {
//         if(cit[i]) a.back().push_back(i);
//         for(int c : adj[i]) {
//             if(c != p) {
//                 self(self, c, i);
//             }
//         }
//     };

//     for(int c : adj[s]) {
//         a.push_back({});
//         dfs2(dfs2, c, s);
//         if(a.back().size()) {
//             pq.push(array<int,2>{(int)a.back().size(), (int)a.size() - 1});
//         }
//     }

//     if(cit[s]) {
//         pq.push({1,(int)a.size()});    
//         a.push_back({s});
//     }

//     vector<array<int,2>> res;
//     while(pq.size()) {
//         array<int,2> b = pq.top();
//         pq.pop();
//         array<int,2> c = pq.top();
//         pq.pop();
//         // cout << "b : " << b << " c : " << c << '\n';
//         // cout << "a[b[1]] : " << a[b[1]] << " a[c[1]] : " << a[c[1]] << '\n';
//         res.push_back({a[b[1]].back(), a[c[1]].back()});
//         a[b[1]].pop_back();
//         a[c[1]].pop_back();
//         if(a[b[1]].size()) {
//             pq.push({(int)a[b[1]].size(), b[1]});
//         }
//         if(a[c[1]].size()) {
//             pq.push({(int)a[c[1]].size(), c[1]});
//         }
//     }

//     cout << 1 << '\n';
//     cout << s + 1 << '\n';
//     for(int i = 0; i < k; i++) {
//         cout << res[i][0] + 1 << " " << res[i][1] + 1 << " " << s + 1 << '\n';
//     }

//     return 0;
// }