#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

bool dfs(int i, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &dead, vector<int> &order) {
    // cout << "dfs: " << i << "\n";
    if(dead[i]) return false;
    order.push_back(i);
    if(visited[i]) return true;
    visited[i] = true;
    for(auto x : adj[i]) {
        if(dfs(x,adj,visited,dead,order)) return true;
    }
    dead[i] = 1;
    order.pop_back();
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> ingoing(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        a--; b--;
        adj[a].push_back(b);
        ingoing[b]++;
    }
    vector<bool> dead(n);
    for(int i = 0; i < n; i++) {
        if(adj[i].empty() || ingoing[i] == 0) {
            dead[i] = 1;
        }
    }

    vector<int> ans;
    vector<bool> visited(n);
    for(int i = 0; i < n; i++) {
        if(!dead[i]) {
            // cout << "start dfs: " << i << '\n';
            dfs(i, adj, visited, dead, ans);
            if(ans.size()) break;
        }
    }

    if(ans.size()) {
        int start = -1;
        for(int i = 0; i < ans.size(); i++) {
            if(ans[i] == ans.back()) {
                start = i;
                break;
            }
        }
        // for(auto &x : ans) cout << ++x << " ";
        cout << ans.size() - start << "\n";
        for(int i = 0; i < ans.size(); i++) {
            if(i >= start) cout << ++ans[i] << " ";
        }

    } else {
        cout << "IMPOSSIBLE\n";
    }

    return 0;
}