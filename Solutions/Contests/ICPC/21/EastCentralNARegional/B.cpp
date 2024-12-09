#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

int lifts[20][100000];
int depths[100000];

void calc_depth(int cur, int p, vector<vector<int>>& c, vector<int>& depth, vector<int>& a, vector<int>& col) {
    depth[cur] = a[cur];
    if(p != -1){
        depth[cur] += depth[p];
        col[cur] = col[p];
    }
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        calc_depth(next, cur, c, depth, a, col);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int m;
    cin >> m;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<vector<int>> adj(n);
    vector<int> indeg(n, 0);
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        u --;
        v --;
        adj[u].push_back(v);
        indeg[v] ++;
    }
    vector<int> depth(n, 0);
    vector<int> roots, col(n, -1);


    auto parent_dfs = [&](auto self, int i, int p, int d) -> void {
        lifts[0][i] = p;
        depths[i] = d;
        for(int c : adj[i]) {
            self(self, c, i, d + 1);
        }
    };

    for(int i = 0; i < n; i++){
        if(indeg[i] == 0){
            col[i] = i;
            calc_depth(i, -1, adj, depth, a, col);
            parent_dfs(parent_dfs, i, i, 0);
        }
    }

    for(int i = 1; i < 20; i++) {
        for(int j = 0; j < n; j++) {
            lifts[i][j] = lifts[i-1][lifts[i-1][j]];
        }
    }

    auto find_lca = [&](int a, int b) -> int {
        if(depths[a] > depths[b]) {
            swap(a,b);
        }
        int diff = depths[b] - depths[a];
        for(int i = 0; i < 20; i++) {
            if((diff >> i) & 1) {
                b = lifts[i][b];
            }
        }
        for(int i = 19; i >= 0; i--) {
            if(lifts[i][a] != lifts[i][b]) {
                a = lifts[i][a];
                b = lifts[i][b];
            }
        }
        if(a != b) {
            a = lifts[0][a];
        }
        return a;
    };

    int ans = 1e9;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(adj[i].size() != 0 || adj[j].size() != 0){
                continue;
            }
            // cout << i << " " << j << " " << col[i] << " " << col[j] << "\n";
            int cans = depth[i] + depth[j];
            if(col[i] == col[j]){
                
                int lca = find_lca(i, j);
                cans -= depth[lca];
                // cout << "LCA : " << lca << " " << depth[lca] << "\n";
            }
            ans = min(ans, cans);
        }
    }
    cout << ans << "\n";

    return 0;
}