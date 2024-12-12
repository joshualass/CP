#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, h;
    cin >> n >> m >> h;

    vector<int> u(n);
    for (int i = 0; i < n; ++i) {
        cin >> u[i];
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int c1, c2;
        cin >> c1 >> c2;
        --c1; --c2;
        if ((u[c1] + 1) % h == u[c2]) {
            adj[c1].push_back(c2);
        }
        if ((u[c2] + 1) % h == u[c1]) {
            adj[c2].push_back(c1);
        }
    }

    if (m == 0) {
        cout << 1 << endl;
        cout << 1 << endl;
        return 0;
    }

    int min_shift = n + 1;
    vector<int> min_shift_nodes;

    for (int i = 0; i < n; ++i) {
        vector<int> shift_nodes = {i};
        vector<bool> shifted(n, false);
        shifted[i] = true;
        vector<int> q = {i};
        int head = 0;

        while (head < q.size()) {
            int u = q[head++];
            for (int v : adj[u]) {
                if (!shifted[v]) {
                    shifted[v] = true;
                    shift_nodes.push_back(v);
                    q.push_back(v);
                }
            }
        }
        
        bool valid_shift = true;
        for (int node : shift_nodes) {
            for (int neighbor : adj[node]) {
                if (!shifted[neighbor]) {
                   valid_shift = false;
                   break; 
                }
            }
             if (!valid_shift) break;
        }

        if (valid_shift) {
            if (shift_nodes.size() < min_shift) {
                min_shift = shift_nodes.size();
                min_shift_nodes = shift_nodes;
            }
        }

    }
    cout << min_shift << endl;
    for (int i = 0; i < min_shift_nodes.size(); i++) {
        cout << min_shift_nodes[i] + 1 << (i == min_shift_nodes.size() - 1 ? "" : " ");
    }
    cout << endl;


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

// void kdfs(int i, vector<vector<int>> &adj, vector<int> &order, vector<int> &vis) {
//     vis[i] = 1;
//     for(int x : adj[i]) {
//         if(vis[x] == 0) {
//             kdfs(x,adj,order,vis);
//         }
//     }
//     order.push_back(i);
// }

// void sdfs(int i, vector<vector<int>> &adj, vector<int> &vis, vector<vector<int>> &sccs) {
//     vis[i] = 2;
//     sccs.back().push_back(i);
//     for(int x : adj[i]) {
//         if(vis[x] == 1) {
//             sdfs(x,adj,vis,sccs);
//         }
//     }
// }

// vector<vector<int>> kosarajus(vector<vector<int>> &adj) {
//     int n = adj.size();
//     vector<vector<int>> tp(n);
//     for(int i = 0; i < n; i++) {
//         for(int x : adj[i]) {
//             tp[x].push_back(i);
//         }
//     }
//     vector<int> order(n);
//     vector<int> vis(n);
//     for(int i = 0; i < n; i++) {
//         if(vis[i] == 0) {
//             kdfs(i,adj,order,vis);
//         }
//     }
//     reverse(order.begin(), order.end());
//     vector<vector<int>> sccs;
//     for(int i = 0; i < n; i++) {
//         if(vis[order[i]] == 1) {
//             sccs.push_back({});
//             sdfs(order[i],tp,vis,sccs);
//         }
//     }
//     return sccs;
// }

// signed main() {
//     ios_base::sync_with_stdio(false);
//     cin.tie(NULL);

//     int n, m, h; cin >> n >> m >> h;
//     vector<int> u(n);
//     for(int &x : u) cin >> x;
//     vector<vector<int>> adj(n);
//     for(int i = 0; i < m; i++) {
//         int c1, c2; cin >> c1 >> c2;
//         c1--; c2--;
//         if((u[c1] + 1) % h == u[c2]) {
//             adj[c1].push_back(c2);
//         }
//         if((u[c2] + 1) % h == u[c1]) {
//             adj[c2].push_back(c1);
//         }
//     }

//     vector<vector<int>> scc = kosarajus(adj);

//     // cout << "scc\n";
//     // for(int i = 0; i < scc.size(); i++) {
//     //     cout << "i : " << i << " scc[i] : " << scc[i] << '\n';
//     // }

//     vector<int> uid(n);
//     for(int i = 0; i < scc.size(); i++) {
//         for(int x : scc[i]) {
//             uid[x] = i;
//         }
//     }

//     vector<int> hasout(scc.size());
//     for(int i = 0; i < n; i++) {
//         for(int t : adj[i]) {
//             if(uid[i] != uid[t]) {
//                 hasout[uid[i]] = 1;
//             }
//         }
//     }

//     // cout << "hasout : " << hasout << '\n';

//     int res = -1;
//     for(int i = 0; i < scc.size(); i++) {
//         if(hasout[i] == 0) {
//             if(res == -1 || scc[i].size() < scc[res].size()) {
//                 res = i;
//             }
//         }
//     }

//     cout << scc[res].size() << '\n';
//     for(int i = 0; i < scc[res].size(); i++) {
//         cout << scc[res][i] + 1 << " \n"[i == scc[res].size() - 1];
//     }

//     return 0;
// }