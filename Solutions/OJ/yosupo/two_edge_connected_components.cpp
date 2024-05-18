#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const ll MOD = 1e9 + 7;

void dfs(int i, int par, vector<vector<int>> &adj, stack<int> &s, vector<int> &times, int &time, vector<vector<int>> &sccs,vector<int> &low, vector<bool> &vis) {
    times[i] = time;    
    low[i] = time++;
    s.push(i);
    vis[i] = 1;

    for(int x : adj[i]) {
        if(x == par) {
            par = -1;
            continue;
        }
        if(times[x] == -1) {
            dfs(x,i,adj,s,times,time,sccs,low,vis);
            low[i] = min(low[i], low[x]);
        } else if(vis[x]) {
            low[i] = min(low[i], times[x]);
        }
    }

    if(low[i] == times[i]) {
        sccs.push_back({});
        while(1) {
            int w = s.top();
            s.pop();
            vis[w] = 0;
            sccs.back().push_back(w);
            if(w == i) break;
        }
    }

}

vector<vector<int>> tarjans(vector<vector<int>> adj) {
    int n = adj.size();
    stack<int> s;
    vector<int> times(n,-1);
    vector<int> low(n);
    vector<vector<int>> sccs;
    vector<bool> vis(n);
    int time = 0;
    for(int i = 0; i < n; i++) {
        if(times[i] == -1) {
            dfs(i,-1,adj,s,times,time,sccs,low,vis);
        }
    }
    return sccs;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    map<pair<int,int>, int> cnts;
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        if(a == b) continue;
        adj[a].push_back(b);
        adj[b].push_back(a);
        cnts[{a,b}]++;
        cnts[{b,a}]++;
    }

    vector<vector<int>> sccs = tarjans(adj);
    cout << sccs.size() << '\n';
    for(auto x : sccs) {
        cout << x.size() << " ";
        for(int i = 0; i < x.size(); i++) {
            cout << x[i] << " \n"[i == x.size() - 1];
        }
    }

    return 0;
}