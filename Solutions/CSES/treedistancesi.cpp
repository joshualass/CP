#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfs1(int i, int p, vector<vector<int>> &adj, vector<pair<int,int>> &bests) {
    
    for(int child : adj[i]) {
        if(child != p) {
            dfs1(child, i, adj, bests);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    
    vector<vector<int>> adj(n);
    vector<pair<int,int>> bests(n,{1,-1}); //subtree size, index
    for(int i = 0; i < n - 1; i++) { //for trees
    // for(int i = 0; i < m; i++) { //for graphs with m edges
        int a, b; cin >> a >> b;
        a--; b--; 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }



    return 0;
}