#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfs1(int i, int p, vector<vector<int>> &adj, vector<pair<pair<int,int>,pair<int,int>>> &bests) {
    
    for(int child : adj[i]) {
        if(child != p) {
            dfs1(child, i, adj, bests);
            if(bests[child].second.first + 1 > bests[i].first.first) {
                bests[i].first = {bests[child].second.first + 1, child};
                if(bests[i].first.first > bests[i].second.first) {
                    swap(bests[i].first, bests[i].second);
                }
            }
        }
    }

}

void dfs2(int i, int p, vector<vector<int>> &adj, vector<pair<pair<int,int>,pair<int,int>>> &bests) {
    if(p != -1) {
        pair<int,int> best_parent = {-1,-1};
        if(bests[p].second.second == i) {
            best_parent = bests[p].first;
        } else {
            best_parent = bests[p].second;
        }
        if(best_parent.first + 1 > bests[i].first.first) {
            bests[i].first = {best_parent.first + 1, p};
            if(bests[i].first.first > bests[i].second.first) {
                swap(bests[i].first, bests[i].second);
            }
        }
    }

    for(int child : adj[i]) {
        if(child != p) {
            dfs2(child, i, adj, bests);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    
    vector<vector<int>> adj(n);
    vector<pair<pair<int,int>,pair<int,int>>>bests(n,{{0,-1},{0,-1}}); //subtree size, index
    for(int i = 0; i < n - 1; i++) { //for trees
    // for(int i = 0; i < m; i++) { //for graphs with m edges
        int a, b; cin >> a >> b;
        a--; b--; 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs1(0,-1,adj,bests);
    dfs2(0,-1,adj,bests);

    for(int i = 0; i < n; i++) {
        cout << bests[i].second.first << " \n"[i == n - 1];
    }

    return 0;
}