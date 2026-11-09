#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
#define sz(x) (int) (x).size()

// {distance, a}
array<int,2> dfs(int i, int p, int d, vector<vector<int>> &adj) {
    array<int,2> res = {d, i};
    for(int c : adj[i]) {
        if(c != p) {
            res = max(res, dfs(c,i,d+1,adj));
        }
    }
    return res;
}

bool find_path(int i, int p, int dest, vector<vector<int>> &adj, vector<int> &path) {
    if(i == dest) {
        path.push_back(i);
        return 1;
    }

    for(int c : adj[i]) {
        if(c != p) {
            if(find_path(c,i,dest,adj,path)) {
                path.push_back(i);
                return 1;
            }
        }
    }

    return 0;
}

//{{a, b, diameter}, path}
pair<array<int,3>,vector<int>> find_diameter(vector<vector<int>> &adj) {
    array<int,2> a = dfs(0,-1,0,adj);
    array<int,2> b = dfs(a[1],-1,0,adj);
    vector<int> path;
    find_path(a[1], -1, b[1], adj, path);
    return {{a[1], b[1], b[0]}, path};
}

void solve() {
    
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // auto dfs = [&](auto self, int i, int p, int d) -> array<int,2> {
    //     array<int,2> res = {d, i};
    //     for(int c : adj[i]) {
    //         if(c != p) {
    //             res = max(res, self(self, c, i, d + 1));
    //         }
    //     }
    //     return res;
    // };

    // auto [dis, f1] = dfs(dfs, 0, -1, 0);

    auto [info, path] = find_diameter(adj);
    if(sz(path) % 2 == 1 && path[sz(path) / 2] == k - 1) {
        cout << "Bob\n";
    } else {
        cout << "Alice\n";
    }


}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    for(int i = 0; i < casi; i++) {

        solve();
    }

    return 0;
}