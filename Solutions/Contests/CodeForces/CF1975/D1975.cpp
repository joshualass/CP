#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

void dfs(int i, int p, int d, vector<int> &vis, vector<vector<int>> &adj) {
    vis[i] = d;
    for(int c : adj[i]) {
        if(c != p) {
            dfs(c,i,d+1,vis,adj);
        }
    }
}

pair<int,int> best_start;
void dfs2(int i, int p, int d, vector<vector<int>> &adj,vector<int> &vis) {
    if(d >= vis[i]) {
        if(d < best_start.first) {
            best_start = {d,i};
        }
    }
    for(int c : adj[i]) {
        if(c != p) {
            dfs2(c,i,d+1,adj,vis);
        }
    }
    
}

int farthest_dist;
void dfs3(int i, int p, int d, vector<vector<int>> &adj) {
    farthest_dist = max(farthest_dist,d);
    for(int c : adj[i]) {
        if(c != p) {
            dfs3(c,i,d+1,adj);
        }
    }
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    int sx, sy; cin >> sx >> sy;
    for(int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    sx--; sy--;
    vector<int> vis(n,-1);
    dfs(sx,-1,0,vis,adj);
    best_start = {INT_MAX, INT_MAX};
    dfs2(sy,-1,0,adj,vis);
    farthest_dist = 0;
    dfs3(best_start.second,-1,0,adj);

    // cout << "bs : " << best_start.first << ", " << best_start.second << " total trav ops : " << (n - 1) * 2 << " saved : " << farthest_dist << '\n';
    cout << best_start.first + (n - 1) * 2 - farthest_dist << '\n';

}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}