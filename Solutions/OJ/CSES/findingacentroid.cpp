#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

//could rewrite to reusable centroid finder 

void calc_subtree_size(int i, int p, int edge_idx, vector<vector<pair<int,int>>> &adj) {
    int size = 1;
    for(int j = 0; j < adj[i].size(); j++) {
        if(adj[i][j].first != p) {
            if(adj[i][j].second == -1) {
                calc_subtree_size(adj[i][j].first, i, j, adj);
            }
            size += adj[i][j].second;
        }
    }
    adj[p][edge_idx].second = size;
}

void calc_subtree_size(int i, int p, int edge_idx, vector<vector<int>> &adj, vector<vector<int>> &subsizes) {
    int size = 1;
    for(int j = 0; j < adj[i].size(); j++) {
        if(adj[i][j] != p) {
            if(subsizes[i][j] == -1) {
                // calc_subtree_size(adj[i][j].first, i, j, adj);
                calc_subtree_size(adj[i][j], i, j, adj, subsizes);
            }
            size += subsizes[i][j];
        }
    }
    // adj[p][edge_idx].second = size;
    subsizes[p][edge_idx] = size;
}

//pass in adj. list, returns centroids :P
vector<int> find_centroids(vector<vector<int>> &adj) {
    int n = adj.size();
    vector<vector<int>> subsizes(n);
    //build subsizes
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < adj[i].size(); j++) {
            subsizes[i].push_back(-1);
        }
    }
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < subsizes[i].size(); j++) {
            if(subsizes[i][j] == -1) {
                calc_subtree_size(adj[i][j], i, j, adj, subsizes);
            }
        }
    }
    vector<int> ans;
    for(int i = 0; i < n; i++) {
        bool ok = 1;
        for(int j = 0; j < subsizes[i].size(); j++) {
            if(subsizes[i][j] > n / 2) {
                ok = 0;
            }
        }
        if(ok) {
            ans.push_back(i);
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    vector<vector<int>> adj(n);

    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << find_centroids(adj).back() + 1 << '\n';
    // int n; cin >> n;

    // vector<vector<pair<int,int>>> adj(n);

    // for(int i = 0; i < n - 1; i++) {
    //     int a, b; cin >> a >> b;
    //     a--; b--;
    //     adj[a].push_back({b,-1});
    //     adj[b].push_back({a,-1});
    // }

    // // for(auto node : adj) {
    // //     for(auto edge : node) {
    // //         if(edge.second == -1) {

    // //         }
    // //     }
    // // }
    // for(int i = 0; i < n; i++) {
    //     for(int j = 0; j < adj[i].size(); j++) {
    //         if(adj[i][j].second == -1) {
    //             calc_subtree_size(adj[i][j].first, i, j, adj);
    //         }
    //     }
    // }

    // int max_size = n / 2;
    // int ans = -1;
    // for(int i = 0; i < n; i++) {
    //     bool ok = 1;
    //     for(int j = 0; j < adj[i].size(); j++) {
    //         // cout << "size of i : " << i << " to " << adj[i][j].first << " is : " << adj[i][j].second << '\n';
    //         if(adj[i][j].second > max_size) {
    //             ok = 0;
    //         }
    //     }
    //     if(ok) {
    //         ans = i;
    //     }
    // }
    // cout << ans + 1 << '\n';
    return 0;
}