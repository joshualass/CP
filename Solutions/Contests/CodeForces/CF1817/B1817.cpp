#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 998244353;

/*
good graph practice
*/

template<typename T>
std::ostream& operator<<(std::ostream& os, set<T> s) {
    for(auto &x: s) os << x << " ";
    return os;
}

void dfs(int i, int p, vector<vector<int>> &adj, vector<int> &vis, int &found, set<int> &bad) {
    // cout << "i : " << i << " p : " << p << " found : " << found << '\n';
    if(vis[i] == -1) {
        found = i;
    }
    vis[i] = p;
    for(int c : adj[i]) {
        if(found == -1 && (vis[c] == -2 || vis[c] == -1)&& bad.count(c) == 0 && c != p) {
            dfs(c,i,adj,vis,found,bad);
        }
    }
    if(found == -1) {
        vis[i] = -3;
    }
    
}

pair<int,vector<int>> findfish(vector<vector<int>> &adj, int i, int b1, int b2) {
    
    set<int> bad = {adj[i][b1], adj[i][b2]};
    vector<int> vis(adj.size(),-2);
    int found = -1;
    
    // cout << "dfs for i : " << i << " bad : " << bad << '\n';
    
    dfs(i,-1,adj,vis,found,bad);
    
    // cout << "found - : " << found << '\n';
    
    return {found, vis};
    
}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    int found = -1;
    int badidx = -1;
    vector<int> p;
    
    vector<array<int,2>> bads = {
        {0,1},
        {0,2},
        {0,3},
        {1,2},
        {1,3},
        {2,3}
    };
    
    for(int i = 0; i < n; i++) {
        if(adj[i].size() >= 4) {
            for(int j = 0; j < 6; j++) {
                auto [ok, vis] = findfish(adj,i,bads[j][0],bads[j][1]);
                if(ok != -1) {
                    found = i;
                    badidx = j;
                    p = vis;
                }
            }
        }
    }
    
    if(found != -1) {
        cout << "Yes\n";
        int curr = p[found];
        int prev = found;
        vector<array<int,2>> res;
        while(curr != found) {
            res.push_back({curr,prev});
            prev = curr;
            curr = p[curr];
        }
        res.push_back({curr,prev});
        res.push_back({found, adj[found][bads[badidx][0]]});
        res.push_back({found, adj[found][bads[badidx][1]]});
        
        cout << res.size() << '\n';
        for(array<int,2> a : res) {
            cout << a[0] + 1 << " " << a[1] + 1 << '\n';
        }
        
    } else {
        cout << "No\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi; cin >> casi;
    while(casi-->0) solve();

    return 0;
}